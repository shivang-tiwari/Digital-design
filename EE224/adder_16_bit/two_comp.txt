library IEEE;
use IEEE.std_logic_1164.all;

entity inverter is
	port(
		b: in bit_VECTOR(15 downto 0);
		s0: in bit;
		o: out bit_VECTOR(15 downto 0));
end entity inverter;

architecture behaviour of inverter is
	signal nb: bit_VECTOR(15 downto 0);
	
	component notgate is
		port(a: in bit;o: out bit);
	end component;
	
	component mux2 is 
		port(s,i0,i1: in bit;o: out bit);
	end component;
	
	begin
		not0:notgate port map(b(0),nb(0));
		not1:notgate port map(b(1),nb(1));
		not2:notgate port map(b(2),nb(2));
		not3:notgate port map(b(3),nb(3));
		not4:notgate port map(b(4),nb(4));
		not5:notgate port map(b(5),nb(5));
		not6:notgate port map(b(6),nb(6));
		not7:notgate port map(b(7),nb(7));
		not8:notgate port map(b(8),nb(8));
		not9:notgate port map(b(9),nb(9));
		not10:notgate port map(b(10),nb(10));
		not11:notgate port map(b(11),nb(11));
		not12:notgate port map(b(12),nb(12));
		not13:notgate port map(b(13),nb(13));
		not14:notgate port map(b(14),nb(14));
		not15:notgate port map(b(15),nb(15));
		muxt0:mux2 port map(s0,b(0),nb(0),o(0));
		muxt1:mux2 port map(s0,b(1),nb(1),o(1));
		muxt2:mux2 port map(s0,b(2),nb(2),o(2));
		muxt3:mux2 port map(s0,b(3),nb(3),o(3));
		muxt4:mux2 port map(s0,b(4),nb(4),o(4));
		muxt5:mux2 port map(s0,b(5),nb(5),o(5));
		muxt6:mux2 port map(s0,b(6),nb(6),o(6));
		muxt7:mux2 port map(s0,b(7),nb(7),o(7));
		muxt8:mux2 port map(s0,b(8),nb(8),o(8));
		muxt9:mux2 port map(s0,b(9),nb(9),o(9));
		muxt10:mux2 port map(s0,b(10),nb(10),o(10));
		muxt11:mux2 port map(s0,b(11),nb(11),o(11));
		muxt12:mux2 port map(s0,b(12),nb(12),o(12));
		muxt13:mux2 port map(s0,b(13),nb(13),o(13));
		muxt14:mux2 port map(s0,b(14),nb(14),o(14));
		muxt15:mux2 port map(s0,b(15),nb(15),o(15));
end behaviour;