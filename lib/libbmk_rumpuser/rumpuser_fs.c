#include <bmk-rumpuser/core_types.h>
#include <bmk-rumpuser/rumpuser.h>
#include <bmk-core/errno.h>
#include <bmk-core/types.h>
#include <bmk-core/string.h>
#include <bmk-core/printf.h>
#include <assert.h>

// Supplied from backing.o file
extern char _binary_data_iso_start;
extern char _binary_data_iso_end;

#define PAWS_SIZE (&_binary_data_iso_end - &_binary_data_iso_start)
char *paws = &_binary_data_iso_start;

//#define PAWS_SIZE 0
//char *paws = NULL;

	int
rumpuser_getfileinfo(const char *name, uint64_t *size, int *type)
{
	int rv;

	if(bmk_strcmp(name, "paws") == 0) {
		*size = (uint64_t)PAWS_SIZE;
		*type = RUMPUSER_FT_BLK;
		rv = 0;
	} else {
		rv = BMK_ENOSYS;
	}

	return rv;
}

	int
rumpuser_open(const char *name, int mode, int *fdp)
{

	int rv;

	if(bmk_strcmp(name, "paws") == 0) {
		*fdp = 0;
		rv = 0;
	} else {
		rv = BMK_ENOSYS;
	}

	return rv;
}

int
rumpuser_close(int fd) {

	bmk_memset(&paws, 0, sizeof(paws));
	return 0;
}

	void
rumpuser_bio(int fd, int op, void *data, size_t dlen, int64_t off,
		rump_biodone_fn biodone, void *donearg)
{

	size_t rv;
	int error;
	size_t pawssize = (size_t)PAWS_SIZE;
	char *returnstr;
	rv = 0; // The amount that is sucessfully read or written
	error = 0;

	assert(donearg != NULL);
	assert(data != NULL);
	assert(off <= PAWS_SIZE);

	assert(pawssize >= dlen);

	if(op & RUMPUSER_BIO_READ)
		returnstr = bmk_memcpy(data, paws + off, dlen); // &paws[off]

	else if(op & RUMPUSER_BIO_WRITE || op & RUMPUSER_BIO_SYNC)
		returnstr = bmk_memcpy(paws + off, data, dlen);

	assert(returnstr != NULL);
	rv = dlen;

	biodone(donearg, rv, error);
}
