/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:44:16 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/26 16:19:32 by xcharra          ###   ########.fr       */
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
         🍦    by nfaust, syluiset & xcharra"

# define DELLINE	"\001\033[2K\r\002"

# define RESET		"\001\033[0;0;0m\002"
# define BOLD		"\001\033[1m\002"
# define FAINT		"\001\033[2m\002"
# define ITALIC		"\001\033[3m\002"
# define UNDERLINE	"\001\033[4m\002"
# define SBLINK		"\001\033[5m\002"
# define FBLINK		"\001\033[6m\002"
# define REVERSE	"\001\033[7m\002"
# define HIDE		"\001\033[8m\002"
# define STRIKE		"\001\033[9m\002"

# define BLACK		"\001\033[30m\002"
# define RED		//"\001\033[31m\002"
# define GREEN		"\001\033[32m\002"
# define YELLOW		"\001\033[33m\002"
# define BLUE		"\001\033[34m\002"
# define PURPLE		"\001\033[35m\002"
# define CYAN		"\001\033[36m\002"
# define GREY		"\001\033[37m\002"

# define LBLACK		"\001\033[90m\002"
# define LRED		"\001\033[91m\002"
# define LGREEN		"\001\033[92m\002"
# define LYELLOW	"\001\033[93m\002"
# define LBLUE		"\001\033[94m\002"
# define LPURPLE	"\001\033[95m\002"
# define LCYAN		"\001\033[96m\002"
# define LWHITE		"\001\033[97m\002"


# define BGBLACK	"\001\033[40m\002"
# define BGRED		"\001\033[41m\002"
# define BGGREEN	"\001\033[42m\002"
# define BGYELLOW	"\001\033[43m\002"
# define BGBLUE		"\001\033[44m\002"
# define BGPURPLE	"\001\033[45m\002"
# define BGCYAN		"\001\033[46m\002"
# define BGGREY		"\001\033[47m\002"

# define LBGBLACK	"\001\033[100m\002"
# define LBGRED		"\001\033[101m\002"
# define LBGGREEN	"\001\033[102m\002"
# define LBGYELLOW	"\001\033[103m\002"
# define LBGBLUE	"\001\033[104m\002"
# define LBGPURPLE	"\001\033[105m\002"
# define LBGCYAN	"\001\033[106m\002"
# define LBGGREY	"\001\033[107m\002"

# define REDPROMPT	" \001\033[4;91m\002TRI_SH $>\001\033[0m\002 "
# define GREPROMPT	" \001\033[4;92m\002TRI_SH $>\001\033[0m\002 "
# define YELPROMPT	" \001\033[4;93m\002TRI_SH $>\001\033[0m\002 "

#endif