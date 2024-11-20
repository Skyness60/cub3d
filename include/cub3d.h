#ifndef CUB3D_H
# define CUB3D_H
# include "../export/ultimatelib.h"
# include <math.h>

# define FOV 66
# define PI 3.14159265358979323846

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct	s_look
{
	t_vec	*pos;
	t_vec	*dir;
	t_vec	*add;
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
	char	**map_copy;
	int		width;
	int		height;
}				t_map;

typedef struct s_cub
{
	char					**file;
	char					*file_without_split;
	t_texture				*texture;
	unsigned long			hex_floor;
	unsigned long			hex_ceiling;
	char					*char_floor;
	char					*char_ceiling;
	t_map					*map;
	int						width;
	int						height;
}				t_cub;

typedef struct s_player
{
	int			nb;
	char		orientation;
	int			x;
	int			y;
}				t_player;


typedef struct	s_data
{
	t_cub					*cub;
	t_player				*player;
	t_garb_c				*trash_ptr;
	t_garb_d				*trash_fds;
	t_look					look;


}				t_data;

// utils
size_t	ft_tablen(char **tab);
void	close_all(t_data *data, char *stingError);
void	replace_tabs_with_spaces(char **map, t_data *data);

// init 
void	init_data(t_data *data);

// free
void	clear_all(t_data *data);

// cub
int		check_name(char *av);
int		set_cub(t_data *data, char *av);
char	**read_cub(char *av, t_data *data);
void	read_map(char **file, t_data *data);
void	read_texture(char **file, t_data *data);
void	check_color(t_data *data, char **tab, int i, bool check);
int		check_xpm(char *av);
int		check_valid_map(t_data *data);
int		check_map(t_data *data);
bool	check_empty_line(t_data *data);
int		verify_win(t_data *data);

// TEMPORAIRE 
void	debug_map(t_data *data);
#endif // !CUB3D_H
