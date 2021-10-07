-- 4 to 1 Multiplexer and 4 to 16 muxbench

library IEEE;
use IEEE.std_logic_1164.all;
entity mux is
	port(s0,s1,d0,d1,d2,d3: in bit;o: out bit);
end entity mux;

entity mux2 is
	port(s,i0,i1: in bit;o: out bit);
end entity mux2;

architecture behaviour of mux is
	signal n0,n1,m0,m1,m2,m3: bit;
	
	component andgate3 is
		port(a,b,c: in bit;o: out bit);
	end component;
	
	component orgate4 is
		port(a,b,c,d: in bit;o: out bit);
	end component;
	
	component notgate is
		port(a: in bit;o: out bit);
	end component;
	
	begin
		not0:notgate port map(s0,n0);
		not1:notgate port map(s1,n1);
		and1:andgate3 port map(n0,n1,d0,m0);
		and2:andgate3 port map(s0,n1,d1,m1);
		and3:andgate3 port map(n0,s1,d2,m2);
		and4:andgate3 port map(s0,s1,d3,m3);
		or1:orgate4 port map(m0,m1,m2,m3,o);
end behaviour;

architecture behaviour of mux2 is
	
	signal a,b,ns: bit;
	
	component andgate is
		port(a,b: in bit;o: out bit);
	end component;

	component orgate is
		port(a,b: in bit;o: out bit);
	end component;

	component notgate is
		port(a: in bit;o: out bit);
	end component;
	
	begin
		
		ag1:andgate port map(s,i1,a);
		ag2:andgate port map(ns,i0,b);
		og:orgate port map(a,b,o);
		nt:notgate port map(s,ns);
end behaviour;


library IEEE;
use IEEE.std_logic_1164.all;

entity muxbench is
	
	port(s0,s1: in bit;
	a: in bit_VECTOR(15 downto 0);
	b: in bit_VECTOR(15 downto 0);
	c: in bit_VECTOR(15 downto 0);
	d: in bit_VECTOR(15 downto 0);
	o: out bit_VECTOR(15 downto 0));
end entity muxbench;	


architecture behaviour of muxbench is
	
	component mux is
		port(s0,s1,d0,d1,d2,d3: in bit;o: out bit);
	end component;
	
	begin
		mux0:mux port map(s0,s1,a(0),b(0),c(0),d(0),o(0));
		mux1:mux port map(s0,s1,a(1),b(1),c(1),d(1),o(1));
		mux2:mux port map(s0,s1,a(2),b(2),c(2),d(2),o(2));
		mux3:mux port map(s0,s1,a(3),b(3),c(3),d(3),o(3));
		mux4:mux port map(s0,s1,a(4),b(4),c(4),d(4),o(4));
		mux5:mux port map(s0,s1,a(5),b(5),c(5),d(5),o(5));
		mux6:mux port map(s0,s1,a(6),b(6),c(6),d(6),o(6));
		mux7:mux port map(s0,s1,a(7),b(7),c(7),d(7),o(7));
		mux8:mux port map(s0,s1,a(8),b(8),c(8),d(8),o(8));
		mux9:mux port map(s0,s1,a(9),b(9),c(9),d(9),o(9));
		mux10:mux port map(s0,s1,a(10),b(10),c(10),d(10),o(10));
		mux11:mux port map(s0,s1,a(11),b(11),c(11),d(11),o(11));
		mux12:mux port map(s0,s1,a(12),b(12),c(12),d(12),o(12));
		mux13:mux port map(s0,s1,a(13),b(13),c(13),d(13),o(13));
		mux14:mux port map(s0,s1,a(14),b(14),c(14),d(14),o(14));
		mux15:mux port map(s0,s1,a(15),b(15),c(15),d(15),o(15));


end behaviour;