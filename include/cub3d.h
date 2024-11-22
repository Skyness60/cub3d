#ifndef CUB3D_H
# define CUB3D_H
# include "../export/ultimatelib.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <X11/keysym.h>

# define PI 3.14159265358979323846
# define FOV PI / 3
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define CELL_SIZE 16


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
	double 		angle;
	int			nb;
	char		orientation;
	double		x;
	double		y;
	double		speed;
}				t_player;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct	s_data
{
	t_cub					*cub;
	t_player				*player;
	t_mlx					*mlx;
	t_garb_c				*trash_ptr;
	t_garb_d				*trash_fds;
	bool					spawn;
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

// raycasting
void	raycasting(t_data *data);

// game
void	open_cub3d(t_data *data);
int		cub3d(t_data *data);
// mlx
void	handle_close(t_data *data);
int		handle_move_keypress(int keycode, t_data *data);
void	handle_move(t_data *data);

// TEMPORAIRE 
void	debug_map(t_data *data);
void	handle_debug_move(t_data *data);
void	print_map_with_player(t_data *data);
#endif // !CUB3D_H
