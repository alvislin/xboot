#ifndef __X86_64_ATOMIC_H__
#define __X86_64_ATOMIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <barrier.h>
#include <irqflags.h>

static inline void atomic_add(long i, atomic_t * v)
{
	irq_flags_t flags;
	long val;

	local_irq_save(flags);
	val = v->counter;
	v->counter = val += i;
	local_irq_restore(flags);
}

static inline long atomic_add_return(long i, atomic_t * v)
{
	irq_flags_t flags;
	long val;

	local_irq_save(flags);
	val = v->counter;
	v->counter = val += i;
	local_irq_restore(flags);

	return val;
}

static inline void atomic_sub(long i, atomic_t * v)
{
	irq_flags_t flags;
	long val;

	local_irq_save(flags);
	val = v->counter;
	v->counter = val -= i;
	local_irq_restore(flags);
}

static inline long atomic_sub_return(long i, atomic_t * v)
{
	irq_flags_t flags;
	long val;

	local_irq_save(flags);
	val = v->counter;
	v->counter = val -= i;
	local_irq_restore(flags);

	return val;
}

#define atomic_set(v, i)			(((v)->counter) = (i))
#define atomic_inc(v)				atomic_add(1, v)
#define atomic_dec(v)				atomic_sub(1, v)
#define atomic_inc_return(v)		(atomic_add_return(1, v))
#define atomic_dec_return(v)		(atomic_sub_return(1, v))
#define atomic_inc_and_test(v)		(atomic_add_return(1, v) == 0)
#define atomic_dec_and_test(v)		(atomic_sub_return(1, v) == 0)
#define atomic_add_negative(i,v)	(atomic_add_return(i, v) < 0)
#define atomic_sub_and_test(i, v)	(atomic_sub_return(i, v) == 0)

#ifdef __cplusplus
}
#endif

#endif /* __X86_64_ATOMIC_H__ */
