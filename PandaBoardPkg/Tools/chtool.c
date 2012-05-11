/*
   2  * chtool.c
   3  *
   4  * Copyright(c) 2010 Texas Instruments.   All rights reserved.
   5  *
   6  * Texas Instruments, <www.ti.com>
   7  * Bastien Allibert <b-allibert@ti.com>
   8  * Olivier Deprez <o-deprez@ti.com>
   9  *
  10  * Redistribution and use in source and binary forms, with or without
  11  * modification, are permitted provided that the following conditions
  12  * are met:
  13  *
  14  *  * Redistributions of source code must retain the above copyright
  15  *    notice, this list of conditions and the following disclaimer.
  16  *  * Redistributions in binary form must reproduce the above copyright
  17  *    notice, this list of conditions and the following disclaimer in
  18  *    the documentation and/or other materials provided with the
  19  *    distribution.
  20  *  * Neither the name Texas Instruments nor the names of its
  21  *    contributors may be used to endorse or promote products derived
  22  *    from this software without specific prior written permission.
  23  *
  24  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  25  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  26  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  27  * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  28  * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  29  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  30  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  31  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  32  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  33  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  34  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  35  */

/*------------------------------ Include Files -------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include "ch_types.h"
#include "ch_omap4.h"
#include "ch_omap5.h"

/*------------------------------ Local Definitions ---------------------------*/


/*------------------------------ Local Types ---------------------------------*/
typedef enum {
	NO_IMAGE,
	PREPENDED_CH,
	MERGED_TOCS
} OutMode_t;
typedef struct {
	char* infile;
	char* outfile;
	char* imagefile;
	OutMode_t OutMode;
	bool_t removeCH;
	outputfile_t out_type;
	OMAP_Platform_t* platform;
} Params_t;

/*------------------------------ Local Variables -----------------------------*/
const OMAP_Platform_t* LV_plist[] = {&CH_OMAP4_Platform,&CH_OMAP5_Platform};

/*------------------------------ Local Constants -----------------------------*/
#define CHTOOL_VERSION "0.4"
#define CH_TRUE  1
#define CH_FALSE 0

/*------------------------------ Local Functions Declarations ----------------*/
int32_t CheckArguments(int argc, char* argv[],Params_t* params);
void PrintPlatformSettings(OMAP_Platform_t* p);
void PrintHelp(char *progname);
int32_t FileExtension(const char *file,const char *pattern);
int32_t dat2bin(Params_t *p);
int32_t bin2dat(Params_t *p);
int32_t RemoveCH(Params_t *p);
int32_t CreateImageFile(Params_t *p);
uint8_t CheckPlatformCompatibilityWithCHFormat(uint8_t *CH,uint32_t FileSize,OMAP_Platform_t* omap);

/*------------------------------ Global Functions ----------------------------*/
/*------------------------------ Local Functions -----------------------------*/


/*------------------------------------------------------------------------------
* FUNCTION   : Main
*
* DESCRIPTION: The function is the top function of the tool, simply calling
*              first the arguments chechker and then the appropriate
*              function, either image generation or extraction.
*
*
* PARAMETERS : argc     - number of arguments
*              argv     - arguments values
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
  Params_t params;

  if (CheckArguments(argc,argv,&params) != 0)
  {
    return 0;
  }

  // TODO : the job
  if (FileExtension(params.infile,"dat") == 0)
  {
	int32_t err_code;
	err_code = dat2bin(&params);
    if (err_code == 0)
	{
		if (params.OutMode != NO_IMAGE)
		{
		  CreateImageFile(&params);
		}
	}
  }
  else if (FileExtension(params.outfile,"dat") == 0)
  {
    int32_t err_code;
    err_code = bin2dat(&params);
	if ((err_code == 0)&&(params.removeCH == CH_TRUE))
	{
		// Remove configuration header from input bin file
		RemoveCH(&params);
	}
  }
  else
  {
    printf("Unrecognized file extension...\n");
  }

  return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : CheckArguments
*
* DESCRIPTION: This function is in charge of checking the command-line
*              arguments given by the user and display the help page
*              in case of troubles.
*
*
* PARAMETERS : argc     - number of arguments
*              argv     - arguments values
*              params   - an empty data structure to store the parameters
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int32_t CheckArguments(int argc, char* argv[],Params_t* params)
{
  int32_t i,j,k;
  
  params->infile    = NULL;
  params->outfile   = NULL;
  params->imagefile = NULL;
  params->OutMode   = NO_IMAGE;
  params->removeCH  = CH_FALSE;
  params->out_type  = BIN_FILE;
  params->platform  = NULL;
  
  if (argc == 1)
  {
    PrintHelp(argv[0]);
    return -1;
  }
  
  for (i=1 ; i<argc ; i++)
  {
    if (strcmp(argv[i],"-p")==0)
	{
		int match=0;
		for (j=0 ; j<(sizeof(LV_plist)/sizeof(const OMAP_Platform_t *)) ; j++)
		{
			int len = strlen(argv[i+1]);
			for(k=0;k<len;k++)
			{
				argv[i+1][k] = toupper(argv[i+1][k]);
			}
			if (strcmp(LV_plist[j]->Name,argv[i+1])==0)
			{
				params->platform = (OMAP_Platform_t*) (LV_plist[j]);
				match=1;
			}
		}
		if (match==0)
		{
			printf("ERROR : Platform %s is not supported...\n",argv[i+1]);
			return -1;
		}
		i++;
	}
	else if (strcmp(argv[i],"-c")==0)
	{
		params->out_type = C_FILE;
	}
	else if (strcmp(argv[i],"-rmch")==0)
	{
		params->removeCH = CH_TRUE;
	}
	else if (strcmp(argv[i],"-m")==0)
	{
		params->imagefile = argv[i+1];
		if (params->outfile == NULL)
		{
			params->outfile = "tmp.bin";
		}
		params->OutMode = MERGED_TOCS;
		i++;
	}
	else if (strcmp(argv[i],"-i")==0)
	{
		params->infile = argv[i+1];
		i++;
	}
	else if (strcmp(argv[i],"-o")==0)
	{
		params->outfile = argv[i+1];
		i++;
	}
	else if (strcmp(argv[i],"-O")==0)
	{
		params->imagefile = argv[i+1];
		if (params->outfile == NULL)
		{
			params->outfile = "tmp.bin";
		}
		params->OutMode = PREPENDED_CH;
		i++;
	}
	else if (strcmp(argv[i],"-v")==0)
	{
		if (params->platform != NULL)
		{
			PrintPlatformSettings(params->platform);
		}
	}	
	else if (strcmp(argv[i],"-h")==0)
	{
		PrintHelp(argv[0]);
		return -1;
	}
	else
	{
		printf("Option %s is not supported...\n",argv[i]);
		printf("Type '%s -h' for more a list of supported options\n",argv[0]);
		return -1;
	}
  }

  if (params->infile == NULL)
  {
    printf("ERROR : Please provide an input file\n");
	return -1;
  }
  if (params->outfile == NULL)
  {
    printf("ERROR : Please provide an output file\n");
	return -1;
  }

  return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : PrintPlatformSettings
*
* DESCRIPTION: This function is in charge of printing to console all
*              the possible parameters supported by a specified platform
*
*
* PARAMETERS : p     - pointer to the data structure describing the platform
*
* RETURNS    : 
*
*-----------------------------------------------------------------------------*/
void PrintPlatformSettings(OMAP_Platform_t* p)
{
	int32_t i,j;
	printf("Platform %s\n",p->Name);
	
	for(i=0 ; i<p->NumberOfSupportedItems ; i++)
	{
		CH_Item_t* it = p->SupportedItemsList[i];
		printf("\tItem %s (size 0x%.4X)\n",it->TOC.Filename,it->TOC.Size);
		for (j=0 ; j<it->numberOfFields ; j++)
		{
			CH_Field f = it->fields[j];
			printf("\t\t0x%.4X %-4d %-32s %-40s 0x%-4.4X\n",f.Offset,f.Size,f.Name,f.Description,f.Value);
		}
	}
	printf("\n\n");
}

/*------------------------------------------------------------------------------
* FUNCTION   : PrintHelp
*
* DESCRIPTION: This function prints the help page to console
*
*
* PARAMETERS : progname     - string containing the program name
*
* RETURNS    : 
*
*-----------------------------------------------------------------------------*/
void PrintHelp(char *progname)
{
	int32_t i;
	printf("\n");
	printf("Version " CHTOOL_VERSION "\n\n");
	
	printf("Usage : %s <options>\n\n",progname);
	
	printf("Options :\n");
	printf("\t-p <platform_name>        : selects the target platform. Supported platforms : ");
	for (i=0 ; i<(sizeof(LV_plist)/sizeof(const OMAP_Platform_t *)) ; i++)
	{
		printf("%s ",LV_plist[i]->Name);
	}
	printf("\n");
	printf("\t-i <input_CH_file>        : input file can be either a *.bin file (for target) or a *.dat file (containing parameters)\n");
	printf("\t-o <output_CH_file>       : output file can be either a *.bin file (for target) or a *.dat file (containing parameters)\n");
	printf("\t-m <merge_file>           : merges the provided signed image's TOC with the configuration header settings\n");
	printf("\t-O <image_file>           : prepend the output CH binary to the provided binary image file\n");
	printf("\t-c                        : generate c file conforming to Topsim format, instead of the usual binary file\n");
	printf("\t-rmch                     : remove the input file's configuration header\n");
	printf("\t-v                        : verbose mode prints to screen all the configuration header fields for the selected platform\n");
	printf("\t-h                        : prints help\n");
	printf("\n\n");
	
	printf("Supported platform(s) : ");
	for (i=0 ; i<(sizeof(LV_plist)/sizeof(const OMAP_Platform_t *)) ; i++)
	{
		printf("%s ",LV_plist[i]->Name);
	}
	printf("\n\n\n");
}

/*------------------------------------------------------------------------------
* FUNCTION   : FileExtension
*
* DESCRIPTION: This function extracts the extension from a filename 
*              and compares it with a specified pattern
*
*
* PARAMETERS : file     - string containing the file name
*              pattern  - pattern to be compared with the file extension
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int32_t FileExtension(const char *file,const char *pattern)
{
	int32_t i,j;
	for (i=strlen(file)-1 ; i>=0 ; i--)
	{
		if (file[i] == '.')
		{
			i++;
			break;
		}
	}
	if (i == 0)
	{
		// No extension found...
		return -1;
	}
	if (strlen(pattern) != (strlen(file) - i))
	{
		// Extension length do not match
		return -1;
	}
	for (j=0 ; j<strlen(pattern) ; j++)
	{
		if (pattern[j] != file[i+j])
		{
			// Mismatch in extension...
			return -1;
		}
	}
	return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : dat2bin
*
* DESCRIPTION: This function generates a binary file containing a 
*              Configuration Header image from a set of parameters given
*              by the user through an input file
*
*
* PARAMETERS : p     - parameters given to the program (including 
*                      input and output filenames
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int32_t dat2bin(Params_t *p)
{
	FILE *inf;
	FILE *outf;
	char myline[128];
	char myword0[128];
	char myword1[128];
	OMAP_Platform_t *omap = p->platform;
	CH_Item_t *item = NULL;
	uint8_t *CH;
	uint8_t *CHt;
	uint32_t idx;
	uint32_t nItems=0;
	uint32_t tmpoffset=0;
    
	// Open files 
	inf = fopen(p->infile,"rb");
	outf = fopen(p->outfile,"wb");
  
	if ((inf == NULL) || (outf == NULL))
	{
		if (inf != NULL)
		{
			fclose(inf);
		}
		if (outf != NULL)
		{
			fclose(outf);
		}
		return -1;
	}

	// If platform is not specified in command-line arguments, try to see if the target is given in the *.dat file
	if (omap == NULL)
	{
		while(fscanf(inf,"%s",myline) != EOF)
		{
			int32_t i,j;
			for (i=0 ; myline[i] != '\0' ; i++)
			{
				if ((myline[i] == ';') || (myline[i] == '#'))
				{
					break;
				}
				if (myline[i] == '=')
				{
					myline[i] = ' ';
					sscanf(myline,"%s %s",myword0,myword1);
					if (strcmp(myword0,"TARGET")==0)
					{
						for(j=0 ; j<sizeof(LV_plist)/sizeof(OMAP_Platform_t*) ; j++)
						{
							if (strcmp(myword1,LV_plist[j]->Name) == 0)
							{
								omap = (OMAP_Platform_t*)LV_plist[j];
								p->platform = omap;
							}
						}
					}
					break;
				}
			}
		}
		fseek(inf,0,SEEK_SET);
	}

  // Check that a platform is specified (for output format choice)
  if (omap == NULL)
  {
	printf("ERROR : Platform must be specified, either in command-line or in provided parameter file\n");
	fclose(inf);
	fclose(outf);
	return -1;
  }
  
  // Allocate Configuration Header memory space
  CH = (uint8_t *)malloc(omap->ConfigurationHeaderSize * sizeof(uint8_t));
  memset(CH,0,omap->ConfigurationHeaderSize * sizeof(uint8_t));

  // Count the number of valid items in image
  while(fscanf(inf,"%s",myline) != EOF)
  {
    int32_t i,j;
	for (i=0 ; myline[i] != '\0' ; i++)
	{
	  if (myline[i] == '=')
      {
	    // If we find a '=', then it is not an item section beginning, so break
	    break;
	  }
	}
	if (myline[i] == '\0')
	{
	  // we came to the end of the line w/o finding a '='.... it seems to be a new item section starting point
	  for (j=0 ; j<omap->NumberOfSupportedItems ; j++)
      {
        if (strcmp(omap->SupportedItemsList[j]->TOC.Filename,myline)==0)
		{
		  nItems++;
          break;
		}
      }
	}
  }
  //printf("Found %d valid items in input file...\n",nItems);

  /* Come back to the beginning of the file */
  fseek(inf,0,SEEK_SET);
  while(fscanf(inf,"%s",myline) != EOF)
  {
    int32_t i,j;
	uint32_t val;

	for (i=0 ; myline[i] != '\0' ; i++)
	{
	  if (myline[i] == '=')
	  {
	    myline[i] = ' ';

		sscanf(myline,"%s %s",myword0,myword1);
		if (strcmp(myword0,"TARGET")==0)
		{
			// Ignore here... only informative
		}
		else
		{
			// Set item attribute
			if ((myword1[0] == '0') && (myword1[1] == 'x'))
			{
			  sscanf(myline,"%s 0x%X",myword0,&val);
			}
			else
			{
			  sscanf(myline,"%s %d",myword0,&val);
			}
			
			//printf("%s <- 0x%X\n",myword0,val);
			
			if (item != NULL)
			{
				for (j=0 ; j<item->numberOfFields ; j++)
				{
					CH_Field f = item->fields[j];
					if (strcmp(f.Name,myword0)==0)
					{
						int32_t k;
						// Write it in little endian !!!
						//printf("fieldSize=%d\n",f.Size);
						for (k=0 ; k<f.Size ; k++)
						{
							uint32_t address = item->TOC.Start + f.Offset + k;
							if (address < omap->ConfigurationHeaderSize)
							{
								CH[address] = (uint8_t)(val & 0xFF);
							}
							else
							{
								printf("ERROR : trying to write on address %d but Configuration Header length is %d. Ignoring...\n",address,omap->ConfigurationHeaderSize);
							}
							//printf("0x%.2X ",val & 0xFF);
							val >>= 8;
						}
						break;
					}
				}
				if (j == item->numberOfFields)
				{
					//printf("WARNING - Could not find field %s in %s item. This input will be ignored...\n",myword0,item->TOC.Filename);
				}
			}
		}
		break;
	  }
	}
	
	if (myline[i] == '\0')
	{
		
		// Change item
		for (j=0 ; j<omap->NumberOfSupportedItems ; j++)
		{
		  if (strcmp(omap->SupportedItemsList[j]->TOC.Filename,myline)==0)
		  {
		    //itemN=j;
			//itemOffset = (nItems+1)*sizeof(CH_ItemTOC_t) + tmpoffset;
			item = omap->SupportedItemsList[j];
			//item->TOC.Start = itemOffset;
			item->TOC.Start = (nItems+1)*sizeof(CH_ItemTOC_t) + tmpoffset;

			//printf("ITEM %s (number %d) : Start=0x%.4X ; Size=%d...\n",myline,itemN,item->TOC.Start,item->TOC.Size);
            tmpoffset += (omap->SupportedItemsList[j]->TOC.Size);		  

			break;
		  }
		}
		if (j==omap->NumberOfSupportedItems)
		{
			//printf("ERROR : Item %s is not supported. Please check your parameter file...\n",myline);
		}
	}
  }

  // ... close the input file
  fclose(inf);  
  
  // Now, write the TOC ...
  for (CHt=CH, idx=0 ; idx<omap->NumberOfSupportedItems ; idx++)
  {
    if (omap->SupportedItemsList[idx]->TOC.Start != 0)
	{
		memcpy(CHt, omap->SupportedItemsList[idx], sizeof(CH_ItemTOC_t));
		CHt += sizeof(CH_ItemTOC_t);
	}
  }
  memset(CHt,0xFF,sizeof(CH_ItemTOC_t));
  
  if (p->out_type == C_FILE)
  {
    int32_t i,j;
    const char *c_header = "#include \"GlobalTypes.h\"\n\n__align(4) const unsigned char LC_Toc[] = \n{\n";
    const char *c_tail = "};\n\n/*================================ End Of File  ==============================*/\n";
	fwrite(c_header,sizeof(uint8_t),strlen(c_header),outf);
	for(i=0 ; i<32 ; i++)
	{
	  for(j=0 ; j<16 ; j++)
	  {
		if ((i == 31) && (j == 15))
		{
			fprintf(outf,"0x%.2x",CH[(i<<4)|j]);
		}
		else
		{
			fprintf(outf,"0x%.2x,  ",CH[(i<<4)|j]);
		}
	  }
	  fprintf(outf,"\n");
	}
	fwrite(c_tail,sizeof(uint8_t),strlen(c_tail),outf);	
  }
  else
  {
	  // Write everything to the output file in standard binary format
	  fwrite(CH,sizeof(uint8_t),omap->ConfigurationHeaderSize,outf);
  }
 
  // ... close the output file
  fclose(outf);

 // Free Configuration Header memory space
  free(CH);

  return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : bin2dat
*
* DESCRIPTION: This function extracts all the parameters stored in a binary 
*              file containing a Configuration Header image and stores them
*              into an output file
*
*
* PARAMETERS : p     - parameters given to the program (including 
*                      input and output filenames
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int32_t bin2dat(Params_t *p)
{
  FILE *inf;
  FILE *outf;
  struct stat FileStat;
  uint32_t FileSize;
  OMAP_Platform_t *omap;
  uint8_t *CH;
  int32_t i,j,k;
  uint8_t MatchFound;
  
  // Open the files
  inf = fopen(p->infile,"rb");
  outf = fopen(p->outfile,"wb");

  if ((inf == NULL) || (outf == NULL))
  {
    if (inf != NULL)
	{
	  fclose(inf);
	}
	if (outf != NULL)
	{
	  fclose(outf);
	}
    return -1;
  }  
  
  // Stat the input file to get the input inage size
  fstat(fileno(inf), &FileStat);
  FileSize = (uint32_t) FileStat.st_size;
  //printf("Input file size is %dbytes\n",FileSize);
  
  // Fill an temporary buffer with the file content
  CH = (uint8_t *)malloc(FileSize * sizeof(uint8_t));
  fread(CH,FileSize,sizeof(uint8_t),inf);
  
  // Close the input file
  fclose(inf);  
  
  if (p->platform == NULL)
  {	
	  // Try to guess the target by parsing the TOC
	  // Browse the supported platform list and take the first platform matching these :
	  //   - The input image size matches the expected configuration header size for the platform
	  //   - All item names (CHSETTINGS, CHRAM,...) contained in the input image are supported by the platform
	  //   - For each of these items, the item data size must match the expected size
	  for (MatchFound=0,i=0 ; (MatchFound==0)&&(i<(sizeof(LV_plist) / sizeof(OMAP_Platform_t*))) ; i++)
	  {
	    omap = (OMAP_Platform_t*) LV_plist[i];
		MatchFound = CheckPlatformCompatibilityWithCHFormat(CH,FileSize,omap);
	  }
	  
	  if (MatchFound==1)
	  {
		printf("Found platform compatibility with %s...\n",omap->Name);
		p->platform = omap;
	  }
	  else
	  {
	    printf("Could not find a compatible platform for this image\n");
		return -1;
	  }
  }
  else
  {
    omap = p->platform;
	MatchFound = CheckPlatformCompatibilityWithCHFormat(CH,FileSize,omap);
	if (MatchFound==0)
	{
	  printf("Compatibility test with %s platform's Configuration Header format FAILED\n", omap->Name);
	  return -1;
	}
  }
  
  if (MatchFound != 0)
  {
	CH_Item_t *item;
	CH_ItemTOC_t *toc;
	
    //OK, do the job !
	fprintf(outf,"TARGET=%s\n",omap->Name);
	
	// Point to the first TOC entry of the input image
	toc = (CH_ItemTOC_t *)CH;
	while(toc->Start != 0xFFFFFFFF)
	{
		for(i=0 ; i<omap->NumberOfSupportedItems ; i++)
		{
			if (strcmp(omap->SupportedItemsList[i]->TOC.Filename,toc->Filename) == 0)
			{
				item = omap->SupportedItemsList[i];
				break;
			}
		}
		// Print the item name
		fprintf(outf,"\n%s\n",toc->Filename);
		
		// Then reverse all the items
		for(j=0 ; j<item->numberOfFields ; j++)
		{
			uint32_t value = 0;
			uint8_t *pvalue = (uint8_t *)&value;
			CH_Field f = item->fields[j];
			
			for(k=0 ; k<f.Size ; k++)
			{
				pvalue[k] = CH[toc->Start + f.Offset + k];
			}
		
			//printf("Field %s value is 0x%.8X\n",f.Name,value);
			fprintf(outf,"%s=0x%.8X\n",f.Name,value);
		}
		
		// Then move to next TOC entry of the input image
		toc++;
	}
  }
  
  // Free the temporary buffer space
  free(CH);
  
  // Close the output file  
  fclose(outf);
  
  return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : bin2dat
*
* DESCRIPTION: This function extracts all the parameters stored in a binary 
*              file containing a Configuration Header image and stores them
*              into an output file
*
*
* PARAMETERS : p     - parameters given to the program (including 
*                      input and output filenames
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int32_t RemoveCH(Params_t *p)
{
  FILE *f;
  struct stat FileStat;
  uint32_t FileSize;
    
  // Open the files
  f = fopen(p->infile,"rb");

  if (f == NULL)
  {
    return -1;
  }  

  // Stat the input file to get the input inage size
  fstat(fileno(f), &FileStat);
  FileSize = (uint32_t) FileStat.st_size;
  //printf("Input file size is %dbytes\n",FileSize);

  if (p->platform != NULL)
  {
	uint8_t *buffer = (uint8_t *)malloc(FileSize * sizeof(uint8_t));
	if (buffer == NULL)
	{
		fclose(f);
		return -1;
	}

	fread((void *)buffer,sizeof(uint8_t),FileSize,f);
	fclose(f);
	f = fopen(p->infile,"wb");
	if (f == NULL)
	{
		free(buffer);
		return -1;
	}

	fwrite((void *)(buffer + p->platform->ConfigurationHeaderSize),sizeof(uint8_t),FileSize - p->platform->ConfigurationHeaderSize,f);
	free(buffer);
  }
  
  fclose(f);  
  return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : CreateImageFile
*
* DESCRIPTION: This function merges configuration header's TOC with
*              a provided signed image's TOC.
*
*
* PARAMETERS : p     - parameters given to the program (including 
*                      config header and signed image filenames
*
* RETURNS    : 0 on success
*              Others on failure
*
*-----------------------------------------------------------------------------*/
int32_t CreateImageFile(Params_t *p)
{
  FILE *chf;
  FILE *sif;
  struct stat FileStat;
  uint32_t ch_size,si_size;
  uint8_t *CH;
  uint8_t *SI;
  CH_ItemTOC_t *toc_entry;
  uint32_t ch_tocsize;
  uint32_t si_tocsize;
  uint32_t new_tocsize;
  uint32_t ch_itemsize;
  

  // Open the files
  chf = fopen(p->outfile,"rb");   /* config header file */
  sif = fopen(p->imagefile,"rb"); /* signed image file */

  if ((chf == NULL) || (sif == NULL))
  {
    if (chf != NULL)
	{
	  fclose(chf);
	}
	if (sif != NULL)
	{
	  fclose(sif);
	}
    return -1;
  }

  // Stat the CH file to get the CH image size
  fstat(fileno(chf), &FileStat);
  ch_size = (uint32_t) FileStat.st_size;
  
  // Fill an temporary buffer with the CH file content
  CH = (uint8_t *)malloc(ch_size * sizeof(uint8_t));
  fread(CH,ch_size,sizeof(uint8_t),chf);
  
  // Close the CH file
  fclose(chf);
   
  // Stat the signed image file to get the signed image size
  fstat(fileno(sif), &FileStat);
  si_size = (uint32_t) FileStat.st_size;
  
  // Fill an temporary buffer with the CH file content
  SI = (uint8_t *)malloc(si_size * sizeof(uint8_t));
  fread(SI,si_size,sizeof(uint8_t),sif);
  
  // Close the CH file
  fclose(sif);  
   
  // Now, analyze SI file's TOC to get its size
  si_tocsize=0;
  for(toc_entry=(CH_ItemTOC_t *)SI ; (toc_entry->Start != 0xFFFFFFFF) ; toc_entry++)
  {
	si_tocsize += (sizeof(CH_ItemTOC_t));
  }

  // Now, analyze CH file's TOC and TOC items to get their sizes
  ch_tocsize=0;
  ch_itemsize=0;
  for(toc_entry=(CH_ItemTOC_t *)CH ; (toc_entry->Start != 0xFFFFFFFF) ; toc_entry++)
  {
	ch_tocsize  += (sizeof(CH_ItemTOC_t));
    ch_itemsize += toc_entry->Size;
  }

  switch (p->OutMode)
  {
	case MERGED_TOCS:
		new_tocsize = ch_tocsize + sizeof(CH_ItemTOC_t) + si_tocsize;
		if (new_tocsize > p->platform->ConfigurationHeaderSize)
		{
			printf("WARNING : Configuration header and image TOC are too big (%d bytes) to fit in the first %d bytes. Program will attempt to prepend CH to image binary file",new_tocsize,p->platform->ConfigurationHeaderSize);
			p->OutMode = PREPENDED_CH;
		}
		else
		{
			break;
		}
    case PREPENDED_CH:
		new_tocsize = ch_tocsize + sizeof(CH_ItemTOC_t);
		if (new_tocsize > p->platform->ConfigurationHeaderSize)
		{
			printf("ERROR : This configuration header is too big (%d bytes) to be prepended to the image file. Maximum supported size is %d bytes.\n",new_tocsize,p->platform->ConfigurationHeaderSize);
			return -1;
		}
		break;		
	default:
		printf("ERROR : This output mode is not supported.\n");
		return -1;
		break;
  }
  
  /* Open the output file (signed image file) */
  sif = fopen(p->imagefile,"wb");                                                              /* signed image file */
  
  /* Process */
  switch (p->OutMode)
  {
	case MERGED_TOCS:
		for(toc_entry=(CH_ItemTOC_t *)CH ; (toc_entry->Start != 0xFFFFFFFF) ; toc_entry++)
		{
			// Add a constant offset to each config header TOC entry, equivalent to the signed image TOC size (overhead of muxing)
			toc_entry->Start += si_tocsize;
		}
		fwrite(CH,sizeof(uint8_t),ch_tocsize,sif);                                                   /* copy configuration header's TOC */
		fwrite(SI,sizeof(uint8_t),si_tocsize + sizeof(CH_ItemTOC_t),sif);                            /* copy signed image's TOC + the TOCEND entry */
		fwrite((void *)(CH + ch_tocsize + sizeof(CH_ItemTOC_t)),sizeof(uint8_t),ch_itemsize,sif);    /* copy configuration header's items */
		fwrite((void *)(SI + si_tocsize + sizeof(CH_ItemTOC_t)),sizeof(uint8_t),p->platform->ConfigurationHeaderSize - (new_tocsize + ch_itemsize),sif); /* Add some padding between configuratino header items and signed image items */
		fwrite((void *)(SI + p->platform->ConfigurationHeaderSize),sizeof(uint8_t),si_size - p->platform->ConfigurationHeaderSize,sif); /* Copy signed image items */
		break;
    case PREPENDED_CH:
		fwrite(CH,sizeof(uint8_t),p->platform->ConfigurationHeaderSize,sif);                         /* copy configuration header */
		fwrite(SI,sizeof(uint8_t),si_size,sif);                                                      /* copy signed image */	
		break;
	default:
		break;
  }
  
  // All changes are done, close the signed image file...
  fclose(sif);
  
  // Free allocated space for input files
  free(CH);
  free(SI);
  
  return 0;
}

/*------------------------------------------------------------------------------
* FUNCTION   : CheckPlatformCompatibilityWithCHFormat
*
* DESCRIPTION: This function analyze a Configuration Header image and
*              tries to determine its compatibility with a given platform,
*              based on the TOC entries and on their respective size
*
*
* PARAMETERS : CH       - input Configuration Header image
*              Filesize - input Configuration Header image size
*              omap     - platform to be checked for compatibility
*
* RETURNS    : 1 in case of compatibility
*              0 in case of incompatibility
*
*-----------------------------------------------------------------------------*/
uint8_t CheckPlatformCompatibilityWithCHFormat(uint8_t *CH,uint32_t FileSize,OMAP_Platform_t* omap)
{
	uint8_t MatchFound=0;
    int j,k;
	
	CH_ItemTOC_t *toc;

	/* commented the following line since file size comparison is not meaningfull when people provides
	not only the config header but also the code image */
    //if (FileSize == omap->ConfigurationHeaderSize)
	{
		for(j=0,toc=(CH_ItemTOC_t *)CH ; toc->Start != 0xFFFFFFFF ; toc++,j++)
		{
			for(MatchFound=0,k=0 ; k<omap->NumberOfSupportedItems ; k++)
			{
				if (strcmp(omap->SupportedItemsList[k]->TOC.Filename,toc->Filename)==0)
				{
					if (omap->SupportedItemsList[k]->TOC.Size == toc->Size)
					{
						MatchFound=1;
					}
					break;
				}
			}
			if (MatchFound==0)
			{
				break;
			}
		}
	}
	return MatchFound;
}

/*-------------------------------End of File ---------------------------------*/
