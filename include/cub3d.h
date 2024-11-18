#ifndef CUB3D_H
# define CUB3D_H
# include "../export/ultimatelib.h"
# include <math.h>

typedef struct	s_look
{
	double	dirX;
	double	dirY;
}	t_look;

typedef enum e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}			t_orientation;

typedef struct	s_texture
{
	char	*path;
	void	*img;
	int		*data;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_map
{
	char	**map;
	int		width;
	int		height;
}				t_map;

typedef struct s_cub
{
	char					**file;
	t_texture				*texture;
	unsigned long			hex_floor;
	unsigned long			hex_ceiling;
	t_map					*map;
	int						width;
	int						height;
}				t_cub;


typedef struct	s_data
{
	t_cub					*cub;
	t_garb_c				*trash_ptr;
	t_garb_d				*trash_fds;
	t_look					look;


}				t_data;

// init 
void	init_data(t_data **data_ptr);

// free
void	clear_all(t_data *data);

// map
int		set_cub(t_data *data, char *av);
#endif // !CUB3D_H
