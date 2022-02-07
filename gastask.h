#ifndef _GASTASK_H_
#define _GASTASK_H_

#include "common.h"

#define MAX_TASKS	200
#define MAX_NETWORKS	200 // jennifer
#define MAX_CPU_FREQS	5
#define MAX_MEMS	5
#define MAX_CLOUD_RATIOS	5 // jennifer
#define MAX_CLOUDS		5 // jennifer
#define MAX_ATTRTYPES	5

typedef struct {
	unsigned char	attrs[MAX_TASKS];
	unsigned	n_tasks_per_type[MAX_ATTRTYPES];
	unsigned	max_type;
} taskattrs_t;

typedef struct {
	taskattrs_t	taskattrs_mem;
	taskattrs_t taskattrs_cloud; // jennifer
	taskattrs_t	taskattrs_cpufreq;
	taskattrs_t	taskattrs_cloudratio; // jennifer
	double		util, power, score;
	struct list_head	list_util;
	struct list_head	list_power;
	struct list_head	list_score;
} gene_t;

typedef struct {
	unsigned	no;
	unsigned	wcet;
	unsigned	period;
	unsigned	memreq;
	double		mem_active_ratio;
} task_t;

typedef struct {
	double		wcet_scale;
	double		power_active, power_idle;	/* per tick */
} cpufreq_t;

// jennifer
typedef struct {
	char		*typestr;
	double		wcet_scale;
	double		power_active, power_idle;	/* not used */
	unsigned	max_capacity;
} cloud_t;

// jennifer
typedef struct {
	unsigned	uplink;
	unsigned	downlink;
	unsigned	no;
} network_t;

extern unsigned max_gen;
extern unsigned	n_tasks;
extern unsigned	n_cpufreqs;
extern unsigned	n_cloudratios; // jennifer
extern unsigned n_clouds; // jennifer
extern unsigned	n_pops;
extern unsigned n_networks; // jennifer

extern struct list_head	genes_by_util;
extern struct list_head	genes_by_power;
extern gene_t	*genes;
extern cpufreq_t	cpufreqs[];
extern double	cloudratios[]; // jennifer
extern cloud_t	clouds[]; // jennifer
extern network_t networks[]; // jennifer

extern double	cutoff, penalty;

extern double	power_consumed_cpu_active;
extern double	power_consumed_mem_active;
extern double	power_consumed_cpu_idle;
extern double	power_consumed_mem_idle;

void add_mem(const char *typestr, unsigned max_capacity, double wcet_scale, double power_active, double power_idle);
void add_cpufreq(double wcet_scale, double power_active, double power_idle);
void add_task(unsigned wcet, unsigned period, unsigned memreq, double mem_active_ratio);
void add_cloudratio(double r); //jennifer
void add_cloud(const char *typestr, double wcet_scale, double power_active, double power_idle, unsigned max_capacity); // jennifer
void add_network(unsigned uplink, unsigned downlink); // jennifer

void get_task_utilpower(unsigned no_task, unsigned char mem_type, unsigned char cloud_type, unsigned char cpufreq_type, double *putil, double *ppower_cpu, double *ppower_mem, double *pdeadline);
unsigned get_task_memreq(unsigned no_task);

void init_report(void);
void close_report(void);
void add_report(unsigned gen);

void run_GA(void);

#endif
