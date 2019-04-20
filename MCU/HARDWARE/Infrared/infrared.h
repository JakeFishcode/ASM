#ifndef __infrared_h
#define __infrared_h
#include "sys.h"

#define F0 PBin(4)	 //前边三路红外
#define F1 PBin(5)
#define F2 PBin(6)

#define L0 PBin(13)	 //左边三路红外
#define L1 PBin(14)
#define L2 PBin(15)

void infrared_init(void);



#endif



