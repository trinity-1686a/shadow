
/*
 * The Shadow Simulator
 * See LICENSE for licensing information
 */
// clang-format off

#ifndef shim_helpers_h
#define shim_helpers_h

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#define SIMULATION_START_SEC 946684800ull

#define SHD_STANDARD_SIGNAL_MAX_NO 31

// Lowest and highest valid realtime signal, according to signal(7).  We don't
// use libc's SIGRTMIN and SIGRTMAX directly since those may omit some signal
// numbers that libc reserves for its internal use. We still need to handle
// those signal numbers in Shadow.
#define SHD_SIGRT_MIN 32

#define SHD_SIGRT_MAX 64

// Definition is sometimes missing in the userspace headers. We could include
// the kernel signal header, but it has definitions that conflict with the
// userspace headers.
#define SS_AUTODISARM (1 << 31)

typedef enum ShdKernelDefaultAction {
  SHD_KERNEL_DEFAULT_ACTION_TERM,
  SHD_KERNEL_DEFAULT_ACTION_IGN,
  SHD_KERNEL_DEFAULT_ACTION_CORE,
  SHD_KERNEL_DEFAULT_ACTION_STOP,
  SHD_KERNEL_DEFAULT_ACTION_CONT,
} ShdKernelDefaultAction;

// An instant in time (analagous to std::time::Instant) in the Shadow
// simulation.
typedef struct EmulatedTime EmulatedTime;

typedef struct SimulationTime SimulationTime;

// Emulation time in nanoseconds. Allows for a consistent representation
// of time throughput the simulator. Emulation time is the simulation time
// plus the EMULATION_TIME_OFFSET. This type allows us to explicitly
// distinguish each type of time in the code.
typedef uint64_t CEmulatedTime;

typedef uint64_t CSimulationTime;

// Compatible with the Linux kernel's definition of sigset_t on x86_64.
//
// This is analagous to, but typically smaller than, libc's sigset_t.
typedef struct shd_kernel_sigset_t {
  uint64_t val;
} shd_kernel_sigset_t;
#define shd_kernel_sigset_t_EMPTY (shd_kernel_sigset_t){ .val = 0 }
#define shd_kernel_sigset_t_FULL (shd_kernel_sigset_t){ .val = ~0 }

// In C this is conventioanlly an anonymous union, but those aren't supported
// in Rust. https://github.com/rust-lang/rust/issues/49804
typedef union ShdKernelSigactionUnion {
  void (*ksa_handler)(int32_t);
  void (*ksa_sigaction)(int32_t, siginfo_t*, void*);
} ShdKernelSigactionUnion;

// Compatible with kernel's definition of `struct sigaction`. Different from
// libc's in that `ksa_handler` and `ksa_sigaction` are explicitly in a union,
// and that `ksa_mask` is the kernel's mask size (64 bits) vs libc's larger one
// (~1000 bits for glibc).
//
// We use the field prefix ksa_ to avoid conflicting with macros defined for
// the corresponding field names in glibc.
typedef struct shd_kernel_sigaction {
  union ShdKernelSigactionUnion u;
  int32_t ksa_flags;
  void (*ksa_restorer)(void);
  struct shd_kernel_sigset_t ksa_mask;
} shd_kernel_sigaction;

#define EMUTIME_INVALID UINT64_MAX

#define EMUTIME_MAX (UINT64_MAX - 1)

#define EMUTIME_MIN 0ull

// The number of nanoseconds from the epoch to January 1st, 2000 at 12:00am UTC.
// This is used to emulate to applications that we are in a recent time.
#define EMUTIME_SIMULATION_START (946684800ull * 1000000000ull)

// Duplicated as EmulatedTime::UNIX_EPOCH
#define EMUTIME_UNIX_EPOCH 0ull







// Invalid simulation time.
#define SIMTIME_INVALID UINT64_MAX

// Maximum and minimum valid values.
#define SIMTIME_MAX 17500059273709551614ull

#define SIMTIME_MIN 0ull

// Represents one nanosecond in simulation time.
#define SIMTIME_ONE_NANOSECOND 1ull

// Represents one microsecond in simulation time.
#define SIMTIME_ONE_MICROSECOND 1000ull

// Represents one millisecond in simulation time.
#define SIMTIME_ONE_MILLISECOND 1000000ull

// Represents one second in simulation time.
#define SIMTIME_ONE_SECOND 1000000000ull

// Represents one minute in simulation time.
#define SIMTIME_ONE_MINUTE 60000000000ull

// Represents one hour in simulation time.
#define SIMTIME_ONE_HOUR 3600000000000ull











CEmulatedTime emutime_add_simtime(CEmulatedTime lhs, CSimulationTime rhs);

CSimulationTime emutime_sub_emutime(CEmulatedTime lhs, CEmulatedTime rhs);

struct shd_kernel_sigset_t shd_sigemptyset(void);

struct shd_kernel_sigset_t shd_sigfullset(void);

void shd_sigaddset(struct shd_kernel_sigset_t *set, int32_t signo);

void shd_sigdelset(struct shd_kernel_sigset_t *set, int32_t signo);

bool shd_sigismember(const struct shd_kernel_sigset_t *set, int32_t signo);

bool shd_sigisemptyset(const struct shd_kernel_sigset_t *set);

struct shd_kernel_sigset_t shd_sigorset(const struct shd_kernel_sigset_t *lhs,
                                        const struct shd_kernel_sigset_t *rhs);

struct shd_kernel_sigset_t shd_sigandset(const struct shd_kernel_sigset_t *lhs,
                                         const struct shd_kernel_sigset_t *rhs);

struct shd_kernel_sigset_t shd_signotset(const struct shd_kernel_sigset_t *set);

int32_t shd_siglowest(const struct shd_kernel_sigset_t *set);

enum ShdKernelDefaultAction shd_defaultAction(int32_t signo);

CSimulationTime simtime_from_timeval(struct timeval val);

CSimulationTime simtime_from_timespec(struct timespec val);

__attribute__((warn_unused_result))
bool simtime_to_timeval(CSimulationTime val,
                        struct timeval *out);

__attribute__((warn_unused_result))
bool simtime_to_timespec(CSimulationTime val,
                         struct timespec *out);

#endif /* shim_helpers_h */
