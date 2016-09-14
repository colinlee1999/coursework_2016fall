//TODO: add error message if malloc fails

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"

void
usage(char *prog)
{
	fprintf(stderr, "usage: %s <-i input file> <-o output file>\n", prog);
	exit(1);
}

static int
cmp_rec_dataptr_t(const void * p1, const void * p2)
{
  rec_dataptr_t * r1 = (rec_dataptr_t *)p1;
  rec_dataptr_t * r2 = (rec_dataptr_t *)p2;
  if (r1->key < r2->key)
    return -1;
  if (r1->key > r2->key)
    return 1;
  return 0;
}

int
main(int argc, char *argv[])
{
  // arguments
  char * inFile = "/no/such/file";
  char * outFile = "/no/such/file";
  int c;

  opterr = 0;
  while ((c = getopt(argc, argv, "i:o:")) != -1) {
    switch (c) {
    case 'i':
      inFile = strdup(optarg);
      break;
    case 'o':
      outFile = strdup(optarg);
      break;
    default:
      usage(argv[0]);
    }
  }

  // open input file
  int fd = open(inFile, O_RDONLY);
  if (fd < 0) {
    perror("open");
    exit(1);
  }

  // open and create output file
  int out_file = open(outFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
  if (out_file < 0) {
    perror("open");
    exit(1);
  }

  // output the number of keys as a header for this file
  int recordsLeft;
  int rc;

  rc = read(fd, &recordsLeft, sizeof(recordsLeft));
  if (rc != sizeof(recordsLeft)) {
    perror("read");
    exit(1);
  }

  rc = write(out_file, &recordsLeft, sizeof(recordsLeft));
  if (rc != sizeof(recordsLeft))
  {
    perror("write");
    exit(1);
  }

  rec_dataptr_t * data_head;
  data_head = (rec_dataptr_t *)malloc(recordsLeft * sizeof(rec_dataptr_t));
  int count = 0;

  while (recordsLeft--) {

    
    // Read the fixed-sized portion of record: key and size of data
    rc = read(fd, data_head + count, sizeof(rec_nodata_t));
    if (rc != sizeof(rec_nodata_t)) {
      perror("read");
      exit(1);
    }

    int num_data_ints = data_head[count].data_ints;

    assert(num_data_ints <= MAX_DATA_INTS);

    data_head[count].data_ptr = (unsigned int *)malloc(num_data_ints * sizeof(unsigned int));

    // Read the variable portion of the record
    rc = read(fd, data_head[count].data_ptr, num_data_ints * sizeof(unsigned int));
    if (rc !=  num_data_ints * sizeof(unsigned int)) {
      perror("read");
      exit(1);
    }

    count++;
  }

  //sort
  qsort(data_head, count, sizeof(rec_dataptr_t), cmp_rec_dataptr_t);

  int i;
  for (i = 0; i < count; i++)
  {
    int data_size = 2 * sizeof(unsigned int) + 
      data_head[i].data_ints * sizeof(unsigned int);
    
    rc = write(out_file, data_head + i, data_size);
    if (rc != data_size)
    {
      perror("write");
      exit(1);
    }
  }
    
  (void) close(fd);
  (void) close(out_file);
  return 0;
}