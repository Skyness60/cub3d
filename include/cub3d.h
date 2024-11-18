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
	t_map			map;
	t_texture		*texture;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;

}				t_data;
#endif // !CUB3D_H