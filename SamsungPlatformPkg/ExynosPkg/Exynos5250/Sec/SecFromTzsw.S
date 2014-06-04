
.text

GCC_ASM_IMPORT(CEntryPoint)
GCC_ASM_EXPORT(_SecEntryFromTzsw)

StartupAddr:	.word	ASM_PFX(CEntryPoint)

ASM_PFX(_SecEntryFromTzsw):
  mov  r0, #0
  ldr  r3, StartupAddr
  blx  r3
 
