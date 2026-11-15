#ifndef MAIN_DEDUP_H
#define MAIN_DEDUP_H
#include "massip-addr.h"

/**
 * The minimum number of buckets in the table. This is the historic
 * default, and is fine for slow scan rates.
 */
#define DEDUP_MIN_ENTRIES 65536

/**
 * The maximum number of buckets we'll auto-scale to. Each bucket
 * holds 4 IPv4 entries of 16 bytes each, so this caps the IPv4
 * table at 128 megabytes.
 */
#define DEDUP_MAX_ENTRIES (1U<<21)

/**
 * The number of seconds worth of responses the table should hold.
 * Targets retransmit SYN-ACKs for several seconds (because we never
 * ACK them), so the table must be big enough that an entry isn't
 * evicted by hash collisions before the retransmissions arrive,
 * otherwise retransmissions get reported as duplicates.
 */
#define DEDUP_WINDOW_SECONDS 10

struct DedupTable *
dedup_create(unsigned bucket_count);

void
dedup_destroy(struct DedupTable *table);

unsigned
dedup_is_duplicate(         struct DedupTable *dedup,
                            ipaddress ip_them, unsigned port_them,
                            ipaddress ip_me, unsigned port_me);

/**
 * Simple unit test
 * @return 0 on success, 1 on failure.
 */
int dedup_selftest(void);


#endif
