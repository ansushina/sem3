#ifndef __FILTER_H__
#define __FILTER_H__

void find_otr(const int *pb, const int *pe, const int **p);

void copy(const int *pb_src, int *pb_dst, const int *p);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif