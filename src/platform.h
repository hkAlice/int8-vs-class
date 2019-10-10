#ifndef __BENCH_PLATFORM_H
#define __BENCH_PLATFORM_H

#ifdef _MSC_VER
#define __attribute__(x) __declspec(noinline) // https://stackoverflow.com/a/3330407
#define __PRETTY_FUNCTION__ __FUNCSIG__ // https://stackoverflow.com/a/48903960
#endif

#endif