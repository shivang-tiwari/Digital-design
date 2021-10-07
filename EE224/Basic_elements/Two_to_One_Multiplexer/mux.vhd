entity mux is
	port(i0,i1,s: in bit;o: out bit);
end entity mux;
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