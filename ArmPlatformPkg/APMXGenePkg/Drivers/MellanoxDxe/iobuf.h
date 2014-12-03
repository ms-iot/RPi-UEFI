/**
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/
#ifndef _IPXE_IOBUF_H
#define _IPXE_IOBUF_H

#include "common.h"
#include "infiniband.h"

/**
 * Minimum I/O buffer length
 *
 * alloc_iob() will round up the allocated length to this size if
 * necessary.  This is used on behalf of hardware that is not capable
 * of auto-padding.
 */
#define IOB_ZLEN 64

/**
 *  * Declare a pointer returned by a function as a unique memory address
 *   * as returned by malloc-type functions.
 *    */
#define __malloc __attribute__ (( malloc ))

/**
 * A persistent I/O buffer
 *
 * This data structure encapsulates a long-lived I/O buffer.  The
 * buffer may be passed between multiple owners, queued for possible
 * retransmission, etc.
 */
struct io_buffer {

	/** Start of the buffer */
	void *head;
	/** Start of data */
	void *data;
	/** End of data */
	void *tail;
	/** End of the buffer */
        void *end;
	size_t len;
	char _data[0];
};

extern size_t iob_cnt;
extern unsigned char iobdb[NUM_IOB_SLOTS][IOB_SLOT_SZ];

/**
 * Reserve space at start of I/O buffer
 *
 * @v iobuf	I/O buffer
 * @v len	Length to reserve
 * @ret data	Pointer to new start of buffer
 */
static inline void * iob_reserve ( struct io_buffer *iobuf, size_t len ) {
	iobuf->data += len;
	iobuf->tail += len;
	return iobuf->data;
}
#define iob_reserve( iobuf, len ) ( {			\
	void *__result;					\
	__result = iob_reserve ( (iobuf), (len) );	\
	assert ( (iobuf)->tail <= (iobuf)->end );	\
	__result; } )

/**
 * Add data to start of I/O buffer
 *
 * @v iobuf	I/O buffer
 * @v len	Length to add
 * @ret data	Pointer to new start of buffer
 */
static inline void * iob_push ( struct io_buffer *iobuf, size_t len ) {
	iobuf->data -= len;
	return iobuf->data;
}
#define iob_push( iobuf, len ) ( {			\
	void *__result;					\
	__result = iob_push ( (iobuf), (len) );		\
	assert ( (iobuf)->data >= (iobuf)->head );	\
	__result; } )

/**
 * Remove data from start of I/O buffer
 *
 * @v iobuf	I/O buffer
 * @v len	Length to remove
 * @ret data	Pointer to new start of buffer
 */
static inline void * iob_pull ( struct io_buffer *iobuf, size_t len ) {
	iobuf->data += len;
	assert ( iobuf->data <= iobuf->tail );
	return iobuf->data;
}
#define iob_pull( iobuf, len ) ( {			\
	void *__result;					\
	__result = iob_pull ( (iobuf), (len) );		\
	assert ( (iobuf)->data <= (iobuf)->tail );	\
	__result; } )

/**
 * Add data to end of I/O buffer
 *
 * @v iobuf	I/O buffer
 * @v len	Length to add
 * @ret data	Pointer to newly added space
 */
static inline void * iob_put ( struct io_buffer *iobuf, size_t len ) {
	void *old_tail = iobuf->tail;
	iobuf->tail += len;
	return old_tail;
}
#define iob_put( iobuf, len ) ( {			\
	void *__result;					\
	__result = iob_put ( (iobuf), (len) );		\
	assert ( (iobuf)->tail <= (iobuf)->end );	\
	__result; } )

/**
 * Remove data from end of I/O buffer
 *
 * @v iobuf	I/O buffer
 * @v len	Length to remove
 */
static inline void iob_unput ( struct io_buffer *iobuf, size_t len ) {
	iobuf->tail -= len;
}
#define iob_unput( iobuf, len ) do {			\
	iob_unput ( (iobuf), (len) );			\
	assert ( (iobuf)->tail >= (iobuf)->data );	\
	} while ( 0 )

/**
 * Empty an I/O buffer
 *
 * @v iobuf	I/O buffer
 */
static inline void iob_empty ( struct io_buffer *iobuf ) {
	iobuf->tail = iobuf->data;
}

/**
 * Calculate length of data in an I/O buffer
 *
 * @v iobuf	I/O buffer
 * @ret len	Length of data in buffer
 */
static inline size_t iob_len ( struct io_buffer *iobuf ) {
	return ( iobuf->tail - iobuf->data );
}

/**
 * Calculate available space at start of an I/O buffer
 *
 * @v iobuf	I/O buffer
 * @ret len	Length of data available at start of buffer
 */
static inline size_t iob_headroom ( struct io_buffer *iobuf ) {
	return ( iobuf->data - iobuf->head );
}

/**
 * Calculate available space at end of an I/O buffer
 *
 * @v iobuf	I/O buffer
 * @ret len	Length of data available at end of buffer
 */
static inline size_t iob_tailroom ( struct io_buffer *iobuf ) {
	return ( iobuf->end - iobuf->tail );
}

/**
 * Create a temporary I/O buffer
 *
 * @v iobuf	I/O buffer
 * @v data	Data buffer
 * @v len	Length of data
 * @v max_len	Length of buffer
 *
 * It is sometimes useful to use the iob_xxx() methods on temporary
 * data buffers.
 */
static inline void iob_populate ( struct io_buffer *iobuf,
				  void *data, size_t len, size_t max_len ) {
	iobuf->head = iobuf->data = data;
	iobuf->tail = ( data + len );
	iobuf->end = ( data + max_len );
}

/**
 * Disown an I/O buffer
 *
 * @v iobuf	I/O buffer
 *
 * There are many functions that take ownership of the I/O buffer they
 * are passed as a parameter.  The caller should not retain a pointer
 * to the I/O buffer.  Use iob_disown() to automatically nullify the
 * caller's pointer, e.g.:
 *
 *     xfer_deliver_iob ( xfer, iob_disown ( iobuf ) );
 *
 * This will ensure that iobuf is set to NULL for any code after the
 * call to xfer_deliver_iob().
 */
#define iob_disown( iobuf ) ( {				\
	struct io_buffer *__iobuf = (iobuf);		\
	(iobuf) = NULL;					\
	__iobuf; } )


static inline void free_iob(struct io_buffer *iobuf)
{
  --iob_cnt;
  iobuf->len = 0;
}

static inline struct io_buffer *alloc_iob(void *data, unsigned int len)
{
  struct io_buffer *iobuf;
  unsigned int x;

  assert (len <= MAX_PACKET_SZ);
  assert (iob_cnt <= NUM_IOB_SLOTS);

  if (unlikely(len > MAX_PACKET_SZ)) {
    ERROR("ERROR: packet too large @%Xh bytes\n", len);
    return NULL;
  }

  /* find next open iobuf slot */
  for (x = 0, iobuf = (struct io_buffer *)iobdb[0]; x < NUM_IOB_SLOTS && iobuf->len != 0; x++) {
    iobuf = (struct io_buffer *)iobdb[x];
  }

  if (unlikely(x >= NUM_IOB_SLOTS)) {
    ERROR("ERROR: out-of-iobuffer-slots\n");
    return NULL;
  }

  iobuf->len = len;
  if (data) {
    memcpy(iobuf->_data, data, len);
  }

  iobuf->head = iobuf->tail = iobuf->data = &iobuf->_data[0];
  iobuf->end = (iobuf->data + len);

  assert(iob_tailroom(iobuf) == len);

  ++iob_cnt;
  DBGC2(data, "iobuf=%p len=%X CNT=%Xh\n", (const CHAR8 *)iobuf, len, iob_cnt);

  return iobuf;
}

#endif /* _IPXE_IOBUF_H */

