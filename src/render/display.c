/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:59 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/16 10:17:04 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void draw_ceiling_and_floor(t_raycast *raycast, int col_size)
{
    int i;

    // Remplir le plafond
    for (i = 0; i < WIN_HEIGHT / 2 - col_size / 2; i++)
        raycast->new_buff[i * WIN_WIDTH + raycast->count_r] = raycast->data->cub->hex_ceiling;

    // Remplir le sol
    for (i = WIN_HEIGHT / 2 + col_size / 2; i < WIN_HEIGHT; i++)
        raycast->new_buff[i * WIN_WIDTH + raycast->count_r] = raycast->data->cub->hex_floor;
}

void draw_column(t_raycast *raycast, t_texture texture, int col_size)
{
    int screen_pos = WIN_HEIGHT / 2 - col_size / 2; // Position de départ dans la colonne

    // Calcul de la coordonnée X de la texture en fonction de l'impact du rayon
    int tex_x = (int)(texture.width * fmod(raycast->precise_hit, 1.0));
    if (tex_x < 0)
        tex_x += texture.width;

    // Calcul de l'index Y dans la texture pour chaque pixel de la colonne
    double tex_step = (double)texture.height / col_size;
    double tex_pos = 0.0;

    // Dessiner chaque pixel de la colonne
    for (int y = 0; y < col_size; y++)
    {
        int screen_y = screen_pos + y;
        if (screen_y >= 0 && screen_y < WIN_HEIGHT)
        {
            // Calcul de la position Y dans la texture en fonction de tex_pos
            int tex_y = (int)tex_pos % texture.height;

            // S'assurer que tex_y est dans les limites de la texture
            if (tex_y < 0)
                tex_y += texture.height;

            // Appliquer la couleur de la texture à la position (tex_x, tex_y)
            raycast->new_buff[screen_y * WIN_WIDTH + raycast->count_r] =
                texture.buffer[tex_y * texture.width + tex_x];
        }
        // Mise à jour de tex_pos pour chaque ligne
        tex_pos += tex_step;
    }
}

void fill_column(t_raycast *raycast, t_texture texture)
{
    double len = (raycast->x == 1) ? raycast->len_x : raycast->len_y;

    // Correction de la distance pour l'effet de perspective


    // Calcul de la taille de la colonne à afficher
    int col_size = (int)(WIN_HEIGHT / len);
    if (col_size > WIN_HEIGHT)
        col_size = WIN_HEIGHT;

    // Dessiner la colonne et remplir le plafond/sol
    draw_column(raycast, texture, col_size);
    if (col_size < WIN_HEIGHT)
        draw_ceiling_and_floor(raycast, col_size);
}

void construct_img(t_data *data, t_raycast *raycast)
{
    // Déterminer la texture à utiliser en fonction de la direction du rayon
    if (raycast->x == 1 && raycast->angle > PI / 2 && raycast->angle < PI + PI / 2)
        fill_column(raycast, data->cub->texture[WEST]);
    else if (raycast->x == 1)
        fill_column(raycast, data->cub->texture[EAST]);
    else if (raycast->angle < PI)
        fill_column(raycast, data->cub->texture[NORTH]);
    else
        fill_column(raycast, data->cub->texture[SOUTH]);
}
