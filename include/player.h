#ifndef PLAYER_H
#define PLAYER_H


class Player
{
	public:
    	Player(int scr=0, int lvl=1, int lf=3, bool slow = false, bool mag=true, bool las=false, bool expand = false, bool div=false);

    	void setScore(int scr) 	    { p_score = scr; }
    	void setLevel(int lvl)     	{ p_level = lvl; }
    	void setLifes(int lf) 	    { p_lifes = lf; }
        void setSlow(bool slow)     { p_slow = slow; }
        void setMagnet(bool mag)    { p_magnet = mag; }
        void setLaser(bool las)     { p_laser = las; }
        void setExpand(bool exp)    { p_expand = exp; }
        void setDivide(bool div)    { p_divide = div; }

    	int score()     { return p_score; }
    	int level()     { return p_level; }
    	int lifes()	    { return p_lifes; }
        bool slow()     { return p_slow; }
        bool magnet()   { return p_magnet; }
        bool laser()    { return p_laser; }
        bool expand()   { return p_expand; }
        bool divide()   { return p_divide; }

    private:
    	int p_score;
    	int p_level;
    	int p_lifes;

        bool p_slow;
        bool p_magnet;
        bool p_laser;
        bool p_expand;
        bool p_divide;
};

#endif