/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 12:47:53 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/28 15:50:02 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H


/*
** Essensial colors
*/

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define ORANGE 0xFFA500
# define LIME 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define FUCHSIA MAGENTA
# define SILVER 0xC0C0C0
# define GRAY 0x808080
# define GREY GRAY
# define MAROON 0x800000
# define OLIVE 0x808000
# define GREEN 0x008000
# define PURPLE 0x800080
# define TEAL 0x008080
# define NAVY 0x000080

/*
** More awesome colors!
*/

/*
** Reds and oranges
*/

# define CRIMSON 0xDC143C
# define CORAL 0xFF7F50
# define INDIAN_RED 0xCD5C5C
# define SALMON 0xFA8072
# define ORANGE_RED 0xFF4500
# define TOMATO 0xFF6347
# define FIREBRICK 0xB22222

/*
** Golds and browns
*/

# define GOLD 0xFFD700
# define GOLDEN_ROD 0xDAA520
# define DARK_GOLDEN_ROD 0xB8860B
# define BROWN 0xA52A2A
# define SADDLEBROWN 0x8B4513
# define CHOCOLATE 0xD2691E
# define PERU 0xCD853F
# define SIENNA 0xA0522D
# define TAN 0xD2B48C
# define ROSY_BROWN 0xBC8F8F

/*
** Greens
*/

# define DARK_GREEN 0x006400
# define LIGHT_GREEN 0x90EE90
# define LAWN_GREEN 0x7CFC00
# define DARK_GREEN 0x006400
# define FOREST_GREEN 0x228B22
# define PALE_GREEN 0x98FB98
# define SPRING_GREEN 0x00FF7F
# define SEA_GREEN 0x2E8B57
# define LIGHT_SEA_GREEN 0x20B2AA

/*
** Blues
*/

# define SLATE_BLUE 0x6A5ACD
# define SLATE_GRAY 0x708090
# define SLATE_GREY SLATE_GRAY
# define DARK_SLATE_GRAY 0x2F4F4F
# define DARK_SLATE_GREY DARK_SLATE_GRAY
# define POWDER_BLUE 0xB0E0E6
# define AQUA_MARINE 0x7FFFD4
# define STEEL_BLUE 0x4682B4
# define SKY_BLUE 0x87CEEB
# define MIDNIGHT_BLUE 0x191970

/*
** Purples
*/

# define INDIGO 0x4B0082
# define DARK_MAGENTA 0x8B008B
# define DEEP_PINK 0xFF1493
# define HOT_PINK 0xFF69B4
# define PINK 0xFFC0CB
# define ORCHID 0xFF83FA

/*
** Off-whites
*/

# define BEIGE 0xF5F5DC
# define ANTIQUE_WHITE 0xFAEBD7
# define WHEAT 0xF5DEB3
# define CORN_SILK 0xFFF8DC
# define LAVENDER 0xE6E6FA
# define FLORAL_WHITE 0xFFFAF0
# define ALICE_BLUE 0xF0F8FF
# define GHOST_WHITE 0xF8F8FF
# define HONEYDEW 0xF0FFF0
# define IVORY 0xFFFFF0
# define AZURE 0xF0FFFF
# define SNOW 0xFFFAFA
# define MISTY_ROSE 0xFFE4E1

/*
** Greys
*/

# define DARK_GRAY 0x696969
# define DARK_GREY DARK_GRAY
# define GAINSBORO 0xDCDCDC
# define WHITE_SMOKE 0xF5F5F5
#endif

# define COLORS_INT (static const int [100]){BLACK, WHITE, RED, ORANGE, LIME, BLUE, YELLOW, CYAN, MAGENTA, FUCHSIA. SILVER. GRAY, GREY, MAROON, OLIVE, PURPLE, TEAL, NAVY. CRIMSON, CORAL, INDIAN_RED, SALMON, ORANGE_RED, TOMATO, FIRE, GOLD, GOLDEN_ROD, DARK_GOLDEN_ROD, BROWN, SADDLEBROWN. CHOCOLATE, PERU, SIENNA, TAN, ROSY_BROWN, DARK_GREEN, LIGHT_GREEN, LAWN_GREEN, DARK_GREEN, FOREST_GREEN, PALE_GREEN, SPRING_GREEN, SEA_GREEN, LIGHT_SEA_GREEN, SLATE_BLUE, SLATE_GRAY, SLATE_GREY, DARK_SLATE_GRAY, DARK_SLATE_GREY, POWDER_BLUE, AQUA_MARINE, STEEL_BLUE, SKY_BLUE, MIDNIGHT_BLUE, INDIGO, DARK_MAGENTA, DEEP_PINK, HOT_PINK, PINK, ORCHID, BEIGE, ANTIQUE_WHITE, WHEAT, CORN_SILK, LAVENDER, FLORAL_WHITE, ALICE_BLUE, GHOST_WHITE, HONEYDEW, IVORY, AZURE, SNOW, MISTY_ROSE, DARK_GRAY, DARK_GREY, GAINSBORO, WHITE_SMOKE, -1}
# define COLORS_CHAR (char *[100]){"BLACK", "WHITE", "RED", "ORANGE", "LIME", "BLUE", "YELLOW", "CYAN", "MAGENTA", "FUCHSIA", "SILVER", "GRAY", "GREY", "MAROON", "OLIVE", "PURPLE", "TEAL", "NAVY", "CRIMSON", "CORAL", "INDIAN RED", "SALMON", "ORANGE RED", "TOMATO", "FIRE", "GOLD", "GOLDEN ROD", "DARK GOLDEN ROD", "BROWN", "SADDLEBROWN". "CHOCOLATE", "PERU", "SIENNA", "TAN", "ROSY BROWN", "DARK GREEN", "LIGHT GREEN", "LAWN GREEN", "DARK GREEN", "FOREST GREEN", "PALE GREEN", "SPRING GREEN", "SEA GREEN", "LIGHT SEA GREEN", "SLATE BLUE", "SLATE_GRAY", "SLATE GREY", "DARK SLATE GRAY", "DARK SLATE GREY", "POWDER BLUE", "AQUA MARINE", "STEEL BLUE", "SKY BLUE", "MIDNIGHT BLUE", "INDIGO", "DARK MAGENTA", "DEEP PINK", "HOT PINK", "PINK", "ORCHID", "BEIGE", "ANTIQUE WHITE", "WHEAT", "CORN SILK", "LAVENDER", "FLORAL WHITE", "ALICE BLUE", "GHOST WHITE", "HONEYDEW", "IVORY", "AZURE", "SNOW", "MISTY ROSE", "DARK GRAY", "DARK GREY", "GAINSBORO", "WHITE SMOKE", NULL}
