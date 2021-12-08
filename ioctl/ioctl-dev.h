#pragma once

#include <linux/types.h>
#include <linux/ioctl.h>

#define TUTORIAL_MAGIC 'k'
#define TUTORIAL_TEST_PRINT _IO(TUTORIAL_MAGIC, 1)
