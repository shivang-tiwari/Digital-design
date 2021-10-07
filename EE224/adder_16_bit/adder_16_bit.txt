-- 16 bit adder
library IEEE;
use IEEE.std_logic_1164.all;
entity adder is
	port(	
		a: in bit_VECTOR(15 downto 0);
		b: in bit_VECTOR(15 downto 0);
		cr0: in bit;
		o: out bit_VECTOR(15 downto 0);
		carry: out bit);
end entity adder;	

architecture struct of adder is
	signal g10,p10,g20,p20,g30,p30,g32,p32,g40,p40,g50,p50,g54,p54,g60,p60,g70,p70,g74,p74,g76,p76,g80,p80,g90,p90,g98,p98,ga0,pa0,gb0,pb0,gb8,pb8,gba,pba,gc0,pc0,gd0,pd0,gdc,pdc,ge0,pe0,gf0,pf0,gf8,pf8,gfc,pfc,gfe,pfe: bit;
	
	signal g,p,pc: bit_vector(15 downto 0);
	
	signal c: bit_vector(15 downto 1);
	
	component prop is
		port(a1,b1,a2,b2: in bit;gi,pi: out bit);
	end component prop;
	
	component andgate is
		port(a,b: in bit;o: out bit);
	end component;
	
	component xorgate is
		port(a,b: in bit;o: out bit);
	end component;
	
	component orgate is
		port(a,b: in bit;o: out bit);
	end component;
	
	begin
		-- pre processing
		and0:andgate port map(a(0),b(0),g(0));
		and1:andgate port map(a(1),b(1),g(1));
		and2:andgate port map(a(2),b(2),g(2));
		and3:andgate port map(a(3),b(3),g(3));
		and4:andgate port map(a(4),b(4),g(4));
		and5:andgate port map(a(5),b(5),g(5));
		and6:andgate port map(a(6),b(6),g(6));
		and7:andgate port map(a(7),b(7),g(7));
		and8:andgate port map(a(8),b(8),g(8));
		and9:andgate port map(a(9),b(9),g(9));
		and10:andgate port map(a(10),b(10),g(10));
		and11:andgate port map(a(11),b(11),g(11));
		and12:andgate port map(a(12),b(12),g(12));
		and13:andgate port map(a(13),b(13),g(13));
		and14:andgate port map(a(14),b(14),g(14));
		and15:andgate port map(a(15),b(15),g(15));
		xor0:xorgate port map(a(0),b(0),p(0));
		xor1:xorgate port map(a(1),b(1),p(1));
		xor2:xorgate port map(a(2),b(2),p(2));
		xor3:xorgate port map(a(3),b(3),p(3));
		xor4:xorgate port map(a(4),b(4),p(4));
		xor5:xorgate port map(a(5),b(5),p(5));
		xor6:xorgate port map(a(6),b(6),p(6));
		xor7:xorgate port map(a(7),b(7),p(7));
		xor8:xorgate port map(a(8),b(8),p(8));
		xor9:xorgate port map(a(9),b(9),p(9));
		xor10:xorgate port map(a(10),b(10),p(10));
		xor11:xorgate port map(a(11),b(11),p(11));
		xor12:xorgate port map(a(12),b(12),p(12));
		xor13:xorgate port map(a(13),b(13),p(13));
		xor14:xorgate port map(a(14),b(14),p(14));
		xor15:xorgate port map(a(15),b(15),p(15));
		--prefix computation
		prop1:prop port map(g(1),p(1),g(0),p(0),g10,p10);
		prop2:prop port map(g(2),p(2),g10,p10,g20,p20);
		prop3:prop port map(g(3),p(3),g(2),p(2),g32,p32);
		prop4:prop port map(g32,p32,g10,p10,g30,p30);
		prop5:prop port map(g(4),p(4),g30,p30,g40,p40);
		prop6:prop port map(g(5),p(5),g(4),p(4),g54,p54);
		prop7:prop port map(g54,p54,g30,p30,g50,p50);
		prop8:prop port map(g(6),p(6),g50,p50,g60,p60);
		prop9:prop port map(g(7),p(7),g(6),p(6),g76,p76);
		prop10:prop port map(g76,p76,g54,p54,g74,p74);
		prop11:prop port map(g74,p74,g30,p30,g70,p70);
		prop12:prop port map(g(8),p(8),g70,p70,g80,p80);
		prop13:prop port map(g(9),p(9),g(8),p(8),g98,p98);
		prop14:prop port map(g98,p98,g70,p70,g90,p90);
		prop15:prop port map(g(10),p(10),g90,p90,ga0,pa0);
		prop16:prop port map(g(11),p(11),g(10),p(10),gba,pba);
		prop17:prop port map(gba,pba,g98,p98,gb8,pb8);
		prop18:prop port map(gb8,pb8,g70,p70,gb0,pb0);
		prop19:prop port map(g(12),p(12),gb0,pb0,gc0,pc0);
		prop20:prop port map(g(13),p(13),g(12),p(12),gdc,pdc);
		prop21:prop port map(gdc,pdc,gb0,pb0,gd0,pd0);
		prop22:prop port map(g(14),p(14),gd0,pd0,ge0,pe0);
		prop23:prop port map(g(15),p(15),g(14),p(14),gfe,pfe);
		prop24:prop port map(gfe,pfe,gdc,pdc,gfc,pfc);
		prop25:prop port map(gfc,pfc,gb8,pb8,gf8,pf8);
		prop26:prop port map(gf8,pf8,g70,p70,gf0,pf0);
		-- post processing
		and16:andgate port map(p10,cr0,pc(1));
		and17:andgate port map(p20,cr0,pc(2));
		and18:andgate port map(p30,cr0,pc(3));
		and19:andgate port map(p40,cr0,pc(4));
		and20:andgate port map(p50,cr0,pc(5));
		and21:andgate port map(p60,cr0,pc(6));
		and22:andgate port map(p70,cr0,pc(7));
		and23:andgate port map(p80,cr0,pc(8));
		and24:andgate port map(p90,cr0,pc(9));
		and25:andgate port map(pa0,cr0,pc(10));
		and26:andgate port map(pb0,cr0,pc(11));
		and27:andgate port map(pc0,cr0,pc(12));
		and28:andgate port map(pd0,cr0,pc(13));
		and29:andgate port map(pe0,cr0,pc(14));
		and30:andgate port map(pf0,cr0,pc(15));
		and31:andgate port map(p(0),cr0,pc(0));
		or0:orgate port map(g(0),pc(0),c(1));
		or1:orgate port map(g10,pc(1),c(2));
		or2:orgate port map(g20,pc(2),c(3));
		or3:orgate port map(g30,pc(3),c(4));
		or4:orgate port map(g40,pc(4),c(5));
		or5:orgate port map(g50,pc(5),c(6));
		or6:orgate port map(g60,pc(6),c(7));
		or7:orgate port map(g70,pc(7),c(8));
		or8:orgate port map(g80,pc(8),c(9));
		or9:orgate port map(g90,pc(9),c(10));
		or10:orgate port map(ga0,pc(10),c(11));
		or11:orgate port map(gb0,pc(11),c(12));
		or12:orgate port map(gc0,pc(12),c(13));
		or13:orgate port map(gd0,pc(13),c(14));
		or14:orgate port map(ge0,pc(14),c(15));
		or15:orgate port map(gf0,pc(15),carry);
		xor16:xorgate port map(p(0),cr0,o(0));
		xor17:xorgate port map(p(1),c(1),o(1));
		xor18:xorgate port map(p(2),c(2),o(2));
		xor19:xorgate port map(p(3),c(3),o(3));
		xor20:xorgate port map(p(4),c(4),o(4));
		xor21:xorgate port map(p(5),c(5),o(5));
		xor22:xorgate port map(p(6),c(6),o(6));
		xor23:xorgate port map(p(7),c(7),o(7));
		xor24:xorgate port map(p(8),c(8),o(8));
		xor25:xorgate port map(p(9),c(9),o(9));
		xor26:xorgate port map(p(10),c(10),o(10));
		xor27:xorgate port map(p(11),c(11),o(11));
		xor28:xorgate port map(p(12),c(12),o(12));
		xor29:xorgate port map(p(13),c(13),o(13));
		xor30:xorgate port map(p(14),c(14),o(14));
		xor31:xorgate port map(p(15),c(15),o(15));
end struct;

-- Carry propogation block
library IEEE;
use IEEE.std_logic_1164.all;
entity prop is
	port(a1,b1,a2,b2: in bit;gi,pi: out bit);
end entity prop;

architecture behaviour of prop is
	signal x: bit;
	component andgate is
		port(a,b: in bit;o: out bit);
	end component;
	
	component orgate is
		port(a,b: in bit;o: out bit);
	end component;
	
	begin
		ag1:andgate port map(b1,a2,x);
		ag2:andgate port map(b1,b2,pi);
		og:orgate port map(a1,x,gi);
end behaviour;