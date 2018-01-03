#define CANIDX_SPD 0
#define CANIDX_ENGRPM 1
#define CANIDX_FUEL_CONSUMPT 2

typedef struct st_data_frame{
  char spd;
  char eng;
  char fuel_consumpt;
}dt_frame;
