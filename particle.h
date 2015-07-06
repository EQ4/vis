
#ifndef VIS_PARTICLE_HEADER_INCLUDED_
#define VIS_PARTICLE_HEADER_INCLUDED_ 1

#include "defines.h"
#include <stdlib.h>

struct particle;

typedef void (*force_fn)(struct particle* p);
typedef void (*limit_fn)(struct particle* p);
typedef void (*mutate_fn)(struct particle* p, double arg);

typedef struct particle {
    double x, y;
    double dx, dy;
    double radius;
    int lifetime;
    int life;
    force_id force;
    limit_id limit;
    void* extra;
} *particle_t;

/* constructors */
particle_t particle_new(double x, double y, double r, int life, void* extra);
particle_t particle_new_full(double x, double y,
                             double ux, double uy,
                             double r, double ur,
                             double ds, double uds,
                             double theta, double utheta,
                             int life, int ulife,
                             force_id force, limit_id limit,
                             void* extra);

/* destructor */
void particle_free(particle_t p);

/* specific mutation functions */
void particle_push(particle_t p, double dx, double dy);
void particle_set_force(particle_t p, force_id force);
void particle_set_limit(particle_t p, limit_id limit);

/* special function for a particle's life to continue */
void particle_tick(particle_t p);

/* accessor functions */
int particle_is_alive(particle_t p);
double particle_get_x(particle_t p);
double particle_get_y(particle_t p);
double particle_get_dx(particle_t p);
double particle_get_dy(particle_t p);
double particle_get_radius(particle_t p);
int particle_get_lifetime(particle_t p);
int particle_get_life(particle_t p);
void* particle_get_extra(particle_t p);

#endif
