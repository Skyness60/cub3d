#ifndef CUB3D_H
# define CUB3D_H
# include "../export/ultimatelib.h"

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

typedef struct	s_data
{
	t_map					*map;
	t_texture				*texture;
	t_garb_c				*trash_ptr;
	t_garb_d				*trash_fds;
	unsigned long			hex_floor;
	unsigned long			hex_ceiling;

}				t_data;

// init 
void	init_data(t_data **data_ptr);

// free
void	clear_all(t_data *data);
#endif // !CUB3D_H