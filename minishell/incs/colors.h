/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:44:16 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/31 12:01:52 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define TRISHBANNER0	"                                                      \
                                           "
# define TRISHBANNER1	".___________..______       __  .__   __.  __       ___\
____. __    __   _______  __       __      "
# define TRISHBANNER2	"|           ||   _  \\     |  | |  \\ |  | |  |     / \
      ||  |  |  | |   ____||  |     |  |     "
# define TRISHBANNER3	"`---|  |----`|  |_)  |    |  | |   \\|  | |  |    |   \
(----`|  |__|  | |  |__   |  |     |  |     "
# define TRISHBANNER4	"    |  |     |      /     |  | |  . `  | |  |     \\  \
 \\    |   __   | |   __|  |  |     |  |     "
# define TRISHBANNER5	"    |  |     |  |\\  \\----.|  | |  |\\   | |  | .----\
)   |   |  |  |  | |  |____ |  `----.|  `----."
# define TRISHBANNER6	"    |__|     | _| `._____||__| |__| \\__| |__| |______\
_/    |__|  |__| |_______||_______||_______|"
# define TRISHBANNER7	"                                                      \
                                           "
# define TRISHBANNER8	"                                                      \
              by nfaust, syluiset & xcharra"


# define RESET		"\x1B[0m"
# define BOLD		"\x1B[1m"
# define FAINT		"\x1B[2m"
# define ITALIC		"\x1B[3m"
# define UNDERLINE	"\x1B[4m"
# define SBLINK		"\x1B[5m"
# define FBLINK		"\x1B[6m"
# define REVERSE	"\x1B[7m"
# define HIDE		"\x1B[8m"
# define STRIKE		"\x1B[9m"

# define BLACK		"\x1B[30m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define PURPLE		"\x1B[35m"
# define CYAN		"\x1B[36m"
# define GREY		"\x1B[37m"

# define LBLACK		"\x1B[90m"
# define LRED		"\x1B[91m"
# define LGREEN		"\x1B[92m"
# define LYELLOW	"\x1B[93m"
# define LBLUE		"\x1B[94m"
# define LPURPLE	"\x1B[95m"
# define LCYAN		"\x1B[96m"
# define LWHITE		"\x1B[97m"


# define BGBLACK	"\x1B[40m"
# define BGRED		"\x1B[41m"
# define BGGREEN	"\x1B[42m"
# define BGYELLOW	"\x1B[43m"
# define BGBLUE		"\x1B[44m"
# define BGPURPLE	"\x1B[45m"
# define BGCYAN		"\x1B[46m"
# define BGGREY		"\x1B[47m"

# define LBGBLACK	"\x1B[100m"
# define LBGRED		"\x1B[101m"
# define LBGGREEN	"\x1B[102m"
# define LBGYELLOW	"\x1B[103m"
# define LBGBLUE	"\x1B[104m"
# define LBGPURPLE	"\x1B[105m"
# define LBGCYAN	"\x1B[106m"
# define LBGGREY	"\x1B[107m"

# define REDPROMPT	" \x1b[4;91mTRI_SH $>\x1b[0m "
# define GREPROMPT	" \x1b[4;92mTRI_SH $>\x1b[0m "
# define YELPROMPT	" \x1b[4;93mTRI_SH $>\x1b[0m "
/*
	printf(BOLD     "Salut\n" RESET);
	printf(FAINT    "Salut\n" RESET);
	printf(ITALIC   "Salut\n" RESET);
	printf(UNDERLINE"Salut\n" RESET);
	printf(SBLINK   "Salut\n" RESET);
	printf(FBLINK   "Salut\n" RESET);
	printf(REVERSE  "Salut\n" RESET);
	printf(HIDE     "Salut\n" RESET);
	printf(STRIKE   "Salut\n" RESET);
	printf("\n");

	printf(LBLACK "Salut\n" RESET);
	printf(LRED   "Salut\n" RESET);
	printf(LGREEN "Salut\n" RESET);
	printf(LYELLOW"Salut\n" RESET);
	printf(LBLUE  "Salut\n" RESET);
	printf(LPURPLE"Salut\n" RESET);
	printf(LCYAN  "Salut\n" RESET);
	printf(LWHITE "Salut\n" RESET);
	printf("\n");

	printf(BLACK "Salut\n" RESET);
	printf(RED   "Salut\n" RESET);
	printf(GREEN "Salut\n" RESET);
	printf(YELLOW"Salut\n" RESET);
	printf(BLUE  "Salut\n" RESET);
	printf(PURPLE"Salut\n" RESET);
	printf(CYAN  "Salut\n" RESET);
	printf(GREY  "Salut\n" RESET);
	printf("\n");

	printf(BGBLACK "Salut\n" RESET);
	printf(BGRED   "Salut\n" RESET);
	printf(BGGREEN "Salut\n" RESET);
	printf(BGYELLOW"Salut\n" RESET);
	printf(BGBLUE  "Salut\n" RESET);
	printf(BGPURPLE"Salut\n" RESET);
	printf(BGCYAN  "Salut\n" RESET);
	printf(BGGREY  "Salut\n" RESET);
	printf("\n");

	printf(LBGBLACK "Salut\n" RESET);
	printf(LBGRED   "Salut\n" RESET);
	printf(LBGGREEN "Salut\n" RESET);
	printf(LBGYELLOW"Salut\n" RESET);
	printf(LBGBLUE  "Salut\n" RESET);
	printf(LBGPURPLE"Salut\n" RESET);
	printf(LBGCYAN  "Salut\n" RESET);
	printf(LBGGREY  "Salut\n" RESET);
*/
#endif