#pragma once
namespace dtg {
	enum SEC {};
	enum BLACK {};
	enum RED {};
	enum GREEN {};
	enum BROWN {};
	enum BLUE {};
	enum PURPLE {};
	enum CYAN {};
	enum GRAY{};
#if 0
	enum GRAY {};
	enum LRED {};
	enum LGREEN {};
	enum YELLOW {};
	enum LBLUE {};
	enum LPURPLE {};
	enum LCYAN {};
	enum WHITE {};
#endif
	enum NORMAL {};//0
	enum BOLD {};//1
	enum UNDER {};//4
	enum BLINK {};//5
	enum REVERSE {};//7

	template<class, class...>
	struct color_internal;

	template<>
	struct color_internal<BLACK> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '0'};
	};

	template<>
	struct color_internal<SEC, BLACK> {
		/*private:*/ const char bg[3] = {';', '4', '0'};
	};

	template<>
	struct color_internal<RED> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '1'};
	};

	template<>
	struct color_internal<SEC, RED> {
		/*private:*/ const char bg[3] = {';', '4', '1'};
	};

	template<>
	struct color_internal<GREEN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '2'};
	};

	template<>
	struct color_internal<SEC, GREEN> {
		/*private:*/ const char bg[3] = {';', '4', '2'};
	};

	template<>
	struct color_internal<BROWN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '3'};
	};

	template<>
	struct color_internal<SEC, BROWN> {
		/*private:*/ const char bg[3] = {';', '4', '3'};
	};
	template<>
	struct color_internal<BLUE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '4'};
	};

	template<>
	struct color_internal<SEC, BLUE> {
		/*private:*/ const char bg[3] = {';', '4', '4'};
	};
	template<>
	struct color_internal<PURPLE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '5'};
	};

	template<>
	struct color_internal<SEC, PURPLE> {
		/*private:*/ const char bg[3] = {';', '4', '5'};
	};
	template<>
	struct color_internal<CYAN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '6'};
	};

	template<>
	struct color_internal<SEC, CYAN> {
		/*private:*/ const char bg[3] = {';', '4', '6'};
	};
	template<>
	struct color_internal<GRAY> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[4] = {'\e', '[', '3', '7'};
	};

	template<>
	struct color_internal<SEC, GRAY> {
		/*private:*/ const char bg[3] = {';', '4', '7'};
	};
#if 0
	template<>
	struct color_internal<GRAY> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '0'};
	};

	template<>
	struct color_internal<SEC, GRAY> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '0'};
	};

	template<>
	struct color_internal<LRED> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '1'};
	};
	template<>
	struct color_internal<SEC, LRED> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '1'};
	};
	template<>
	struct color_internal<LGREEN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '2'};
	};
	template<>
	struct color_internal<SEC, LGREEN> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '2'};
	};
	template<>
	struct color_internal<YELLOW> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '3'};
	};
	template<>
	struct color_internal<SEC, YELLOW> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '3'};
	};
	template<>
	struct color_internal<LBLUE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '4'};
	};
	template<>
	struct color_internal<SEC, LBLUE> {
		/*private:*/ const char fg[5] = {';', '1', ';', '4', '4'};
	};
	
	template<>
	struct color_internal<LPURPLE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '5'};
	};
	
	template<>
	struct color_internal<SEC, LPURPLE> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '5'};
	};
	
	template<>
	struct color_internal<LCYAN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '6'};
	};
	
	template<>
	struct color_internal<SEC, LCYAN> {
		/*private:*/ const char fg[5] = {';', '1', ';', '4', '6'};
	};

	template<>
	struct color_internal<WHITE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\e', '[', '1', ';', '3', '7'};
	};
	
	template<>
	struct color_internal<SEC, WHITE> {
		/*private:*/ const char fg[5] = {';', '1', ';', '4', '7'};
	};
#endif	

	template<>
	struct color_internal<NORMAL> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[3] = {'\e', '[', '0'};
	};

	template<>
	struct color_internal<BOLD> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[3] = {'\e', '[', '1'};
	};

	template<>
	struct color_internal<UNDER> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[3] = {'\e', '[', '4'};
	};
	
	template<>
	struct color_internal<BLINK> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[3] = {'\e', '[', '5'};
	};
	
	template<>
	struct color_internal<REVERSE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[3] = {'\e', '[', '7'};
	};

	template<>
	struct color_internal<SEC, NORMAL> {
		/*private:*/ const char st[2] = {';', '0'};
	};

	template<>
	struct color_internal<SEC, BOLD> {
		/*private:*/ const char st[2] = {';', '1'};
	};

	template<>
	struct color_internal<SEC, UNDER> {
		/*private:*/ const char st[2] = {';', '4'};
	};
	
	template<>
	struct color_internal<SEC, BLINK> {
		/*private:*/ const char st[2] = {';', '5'};
	};
	
	template<>
	struct color_internal<SEC, REVERSE> {
		/*private:*/ const char st[2] = {';', '7'};
	};

	template<>
	struct color_internal<SEC> {
		operator const char *() const {
			return bg;
		}
		/*private:*/ const char bg[2] = {'\e', '['};
	};

	template<class, class...>
	struct color;

	template<class T>
	struct color<T> : color_internal<T>{
		/*private:*/ const char end[2] = {'m', '\0'};
	};

	template<class Fg, class Bg>
	struct color<Fg, Bg> : color_internal<Fg>, color_internal<SEC, Bg>{
		/*private:*/ const char end[2] = {'m', '\0'};
	};

	template<class fg, class bg, class st>
	struct color<fg, bg, st> : color_internal<fg>, color_internal<SEC, bg>, color_internal<SEC, st> {
		/*private:*/ const char end[2] = {'m', '\0'};
	};

	template<class fg, class bg, class st, class st2>
	struct color<fg, bg, st, st2> : color_internal<fg>, color_internal<SEC, bg>, color_internal<SEC, st>, color_internal<SEC, st2> {
		/*private:*/ const char end[2] = {'m', '\0'};
	};

}//namespace dtg






