/**
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/
#ifndef _IPXE_IB_PACKET_H
#define _IPXE_IB_PACKET_H

struct ib_device;
struct ib_queue_pair;
struct ib_address_vector;
struct io_buffer;

/** An Infiniband Globally Unique Identifier */
union ib_guid {
	uint8_t bytes[8];
	uint16_t words[4];
	uint32_t dwords[2];
};

/** An Infiniband Global Identifier */
union ib_gid {
	uint8_t bytes[16];
	uint16_t words[8];
	uint32_t dwords[4];
	struct {
		union ib_guid prefix;
		union ib_guid guid;
	} s;
};

/** Infiniband Globally Unique Identifier debug message format */
#define IB_GUID_FMT "%08x:%08x"

/** Infiniband Globally Unique Identifier debug message arguments */
#define IB_GUID_ARGS( guid ) \
  ntohl ( (guid)->dwords[0] ), ntohl ( (guid)->dwords[1] )

/** Infiniband Global Identifier debug message format */
#define IB_GID_FMT IB_GUID_FMT ":" IB_GUID_FMT

/** Infiniband Global Identifier debug message arguments */
#define IB_GID_ARGS( gid ) \
  IB_GUID_ARGS ( &(gid)->s.prefix ), IB_GUID_ARGS ( &(gid)->s.guid )

/** An Infiniband Local Route Header */
struct ib_local_route_header {
	/** Virtual lane and link version */
	uint8_t vl__lver;
	/** Service level and next link header */
	uint8_t sl__lnh;
	/** Destination LID */
	uint16_t dlid;
	/** Packet length */
	uint16_t length;
	/** Source LID */
	uint16_t slid;
} __attribute__ (( packed ));

/** Infiniband virtual lanes */
enum ib_vl {
	IB_VL_DEFAULT = 0,
	IB_VL_SMP = 15,
};

/** An Infiniband Link Next Header value */
enum ib_lnh {
	IB_LNH_RAW = 0,
	IB_LNH_IPv6 = 1,
	IB_LNH_BTH = 2,
	IB_LNH_GRH = 3
};

/** Default Infiniband LID */
#define IB_LID_NONE 0xffff

/** Test for multicast LID */
#define IB_LID_MULTICAST( lid ) ( ( (lid) >= 0xc000 ) && ( (lid) <= 0xfffe ) )

/** An Infiniband Global Route Header */
struct ib_global_route_header {
	/** IP version, traffic class, and flow label
	 *
	 *  4 bits : Version of the GRH
	 *  8 bits : Traffic class
	 * 20 bits : Flow label
	 */
	uint32_t ipver__tclass__flowlabel;
	/** Payload length */
	uint16_t paylen;
	/** Next header */
	uint8_t nxthdr;
	/** Hop limit */
	uint8_t hoplmt;
	/** Source GID */
	union ib_gid sgid;
	/** Destiniation GID */
	union ib_gid dgid;
} __attribute__ (( packed ));


/** An Infiniband Base Transport Header */
struct ib_base_transport_header {
	/** Opcode */
	uint8_t opcode;
	/** Transport header version, pad count, migration and solicitation */
	uint8_t se__m__padcnt__tver;
	/** Partition key */
	uint16_t pkey;
	/** Destination queue pair */
	uint32_t dest_qp;
	/** Packet sequence number and acknowledge request */
	uint32_t ack__psn;
} __attribute__ (( packed ));

/** An Infiniband BTH opcode */
enum ib_bth_opcode {
	BTH_OPCODE_UD_SEND = 0x64,
};

/** An Infiniband Datagram Extended Transport Header */
struct ib_datagram_extended_transport_header {
	/** Queue key */
	uint32_t qkey;
	/** Source queue pair */
	uint32_t src_qp;
} __attribute__ (( packed ));

/** All known IB header formats */
union ib_headers {
	struct ib_local_route_header lrh;
	struct {
		struct ib_local_route_header lrh;
		struct ib_global_route_header grh;
		struct ib_base_transport_header bth;
		struct ib_datagram_extended_transport_header deth;
	} __attribute__ (( packed )) lrh__grh__bth__deth;
	struct {
		struct ib_local_route_header lrh;
		struct ib_base_transport_header bth;
		struct ib_datagram_extended_transport_header deth;
	} __attribute__ (( packed )) lrh__bth__deth;
} __attribute__ (( packed ));

/** Maximum size required for IB headers */
#define IB_MAX_HEADER_SIZE sizeof ( union ib_headers )

#endif /* _IPXE_IB_PACKET_H */
