/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:38:50 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 17:23:09 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "get_next_line_bonus.h"

# define SIZE 64
# define TRANSPARENT -16777216

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_jump
{
	int	jump_decel;
	int	accel_jump;
	int	max_jump_speed;
}		t_jump;

typedef struct s_gravity
{
	int	accel_gravity;
	int	max_gravity;
}		t_gravity;

typedef struct s_move
{
	int	ismov;
	int	dir;
	int	isjump;
}		t_move;

typedef struct s_object
{
	char	type;
	int		life;
	int		speed;
	int		x;
	int		y;
	int		gravity_force;
	t_move	move;
	t_jump	jump;
}			t_object;

typedef struct s_lay
{
	int	n_row;
	int	n_col;
	int	n_exit;
	int	n_pl;
	int	n_en;
	int	n_collect;
}		t_lay;

typedef struct s_err
{
	int	inv_rowlen;
	int	inv_char;
	int	inv_n_players;
	int	inv_n_enemies;
	int	inv_n_collect;
	int	inv_n_exits;
	int	inv_borders;
}		t_err;

typedef struct s_sprite
{
	t_img		wall;
	t_img		empty;
	t_img		exit;
	t_img		player_falling_right;
	t_img		player_falling_left;
	t_list		*idle_player_left;
	t_list		*idle_player_right;
	t_list		*run_player_left;
	t_list		*run_player_right;
	t_list		*jump_player_left;
	t_list		*jump_player_right;
	t_list		*player_dying_right;
	t_list		*player_dying_left;
	t_list		*idle_collect;
	t_list		*idle_enemy_left;
	t_list		*idle_enemy_right;
	t_list		*run_enemy_left;
	t_list		*run_enemy_right;
	t_list		*enemy_attack_left;
	t_list		*enemy_attack_right;
}				t_sprite;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**map_og;
	t_img		*canva;
	int			height;
	int			width;
	int			n_frames;
	int			g_rate;
	int			redraw;
	int			moves;
	t_list		*collect;
	t_list		*enemies;
	t_sprite	sprites;
	t_lay		layout;
	t_object	*player;
	t_gravity	*gravity;
}		t_game;

//animation
t_list		*load_animation(t_game *data, char *path, int number, int i);
void		free_animation(t_game *data, t_list *lst);
void		put_animation_idle(t_list *animation, int n, t_object *object, \
			int id);
void		put_animation_one_time(t_list *animation, int n, t_object *object, \
			int id);
void		put_moving_animation(t_list *animation, int n, int id, \
			t_object *object);

//canva
void		put_img_to_canva(t_img *canva, t_img *img, int x, int y);
t_img		*new_canva(t_game *data);
void		free_canva(t_game *data);
int			get_color(t_img *img, int x, int y);

//check_path
int			check_path(char **map, t_lay layout);

//checks in game
int			check_collect_dead(t_game *data);
int			check_ending(t_game *data);

//checks
char		**check_map(int ac, char **av, t_lay *layout);
void		check_layout(char *line, t_err *map_err, t_lay *layout, \
			int is_last);
t_lay		new_layout(void);
void		readlayout(int fd, t_err *map_err, t_lay *layout, char **map_str);
int			maybe_print_error(t_err *map_err, char **map_str);

//collect
int			put_collect(t_game *data);
t_list		*init_collects(t_game *data);
int			kill_collect(t_game *data, int x, int y);
int			check_collect_dead(t_game *data);

//enemies
t_list		*init_enemies(t_game *data);
int			put_enemies(t_game *data);
int			check_enemys(t_game *data);
void		move_enemy(t_game *data, t_object *enemy, int i, int *move);

//enemy patrol
int			enemy_patrol(t_game *data, t_object *enemy, int i);

//error
int			error_msg(char *str, char **map);

//ft_split
char		**ft_split(char const *str, char c);

//game_mac or linux
void		game_init(t_game *data, t_lay layout);
int			end_game(t_game *data);
void		new_game(t_game *data);
int			reset_game(t_game *data);

//gravity
t_gravity	*init_gravity(void);
int			on_ground(t_game *data, t_object *object);
void		apply_gravity(t_game *data);

//handle keys
int			handle_keypress(int keysym, t_game *data);
int			handle_keyrele(int keysym, t_game *data);

//lst_functions
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);

//main
int			render(t_game *data);
t_game		*game(void);

//map
char		**get_map(int fd, t_lay *layout);
int			print_map(t_game *data, int flag);

//object
int			object_init(t_game *data, t_object *object, char c);
void		move_object(t_game *data, t_object *object);
int			check_object_colision(t_game *data, t_object *object);

//player
t_object	*new_player(t_game *data);
int			player_jump(t_game *data, int flag);

//put_player
void		put_player(t_game *data);

//sprites
int			free_sprites(t_game *data);
t_sprite	initsprites(t_game *data);
char		*add_number_xpm(char *s1, char c);
void		load_img(t_img *img, char *filename);

//utils
char		*ft_str_add(char *s1, char *s2);
int			ft_countchar(char *str, char c);
int			ft_strnfind(char *s1, char *s2, int n);
void		ft_free_matrix(char ***m);
char		**ft_matrix_dup(char **m);

#endif