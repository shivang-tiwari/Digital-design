library IEEE;
use IEEE.std_logic_1164.all;

entity four_input_xor is
	port(A,B,C,D: in bit;F: out bit);
end entity four_input_xor;
entity mux is
	port(i0,i1,s: in bit;o: out bit);
end mux;

architecture behaviour of four_input_xor is
	signal nb,nd,nboth,xboth1,xboth2: bit;
	component mux is
		port(i0,i1,s: in bit;o: out bit);
	end component;
	begin
		mux1:mux port map('1','0',B,nb);
		mux2:mux port map('1','0',D,nd);
		mux3:mux port map(B,nb,A,xboth1);
		mux4:mux port map(D,nd,C,xboth2);
		mux5:mux port map('1','0',xboth2,nboth);
		mux6:mux port map(xboth2,nboth,xboth1,F);
end behaviour;
entity andgate is
	port(a,b: in bit;o: out bit);
end entity andgate;

entity orgate is
	port(a,b: in bit;o: out bit);
end entity orgate;

entity notgate is
	port(a: in bit;o: out bit);
end entity notgate;
architecture behaviour of andgate is
	begin
	o <= a and b;
end behaviour;
architecture behaviour of orgate is
	begin
	o <= a or b;
end behaviour;
architecture behaviour of notgate is
	begin
	o <= not a ;
end behaviour;
architecture struct of mux is
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
end struct;