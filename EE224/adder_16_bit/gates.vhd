
-- AND, OR,XOR,NAND and NOT gates
library IEEE;
use IEEE.std_logic_1164.all;
entity andgate is
	port(a,b: in bit;o: out bit);
end entity andgate;

entity nandgate is
	port(a,b: in bit;o: out bit);
end entity nandgate;

entity andgate3 is
	port(a,b,c: in bit;o: out bit);
end entity andgate3;

library IEEE;
use IEEE.std_logic_1164.all;

entity xorgate is
	port(a,b: in bit;o: out bit);
end entity xorgate;

library IEEE;
use IEEE.std_logic_1164.all;

entity orgate is
	port(a,b: in bit;o: out bit);
end entity orgate;

library IEEE;
use IEEE.std_logic_1164.all;

entity orgate4 is
	port(a,b,c,d: in bit;o: out bit);
end entity orgate4;

library IEEE;
use IEEE.std_logic_1164.all;

entity notgate is
	port(a: in bit;o: out bit);
end entity notgate;

architecture behaviour of andgate is
	begin
		o <= a and b;
end behaviour;

architecture behaviour of nandgate is
	begin
		o <= a nand b;
end behaviour;

architecture behaviour of andgate3 is
	begin
		o <= a and b and c;
end behaviour;

architecture behaviour of orgate is
	begin
		o <= a or b;
end behaviour;

architecture behaviour of orgate4 is
	begin
		o <= a or b or c or d;
end behaviour;

architecture behaviour of xorgate is
	begin
		o <= a xor b;
end behaviour;

architecture behaviour of notgate is
	begin
		o <= not a ;
end behaviour;

-- 16 input benches


-- nandbench
library IEEE;
use IEEE.std_logic_1164.all;

entity nandbench is
	port(
		a: in bit_VECTOR(15 downto 0);
		b: in bit_VECTOR(15 downto 0);
		o: out bit_VECTOR(15 downto 0));
end entity nandbench;	

architecture struct of nandbench is
	component nandgate is
		port(a,b: in bit;o: out bit);
	end component nandgate;
	begin
		nand0:nandgate port map(a(0),b(0),o(0));
		nand1:nandgate port map(a(1),b(1),o(1));
		nand2:nandgate port map(a(2),b(2),o(2));
		nand3:nandgate port map(a(3),b(3),o(3));
		nand4:nandgate port map(a(4),b(4),o(4));
		nand5:nandgate port map(a(5),b(5),o(5));
		nand6:nandgate port map(a(6),b(6),o(6));
		nand7:nandgate port map(a(7),b(7),o(7));
		nand8:nandgate port map(a(8),b(8),o(8));
		nand9:nandgate port map(a(9),b(9),o(9));
		nand10:nandgate port map(a(10),b(10),o(10));
		nand11:nandgate port map(a(11),b(11),o(11));
		nand12:nandgate port map(a(12),b(12),o(12));
		nand13:nandgate port map(a(13),b(13),o(13));
		nand14:nandgate port map(a(14),b(14),o(14));
		nand15:nandgate port map(a(15),b(15),o(15));
end struct;

-- xorbench
library IEEE;
use IEEE.std_logic_1164.all;

entity xorbench is
	port(
		a: in bit_VECTOR(15 downto 0);
		b: in bit_VECTOR(15 downto 0);
		o: out bit_VECTOR(15 downto 0));
end entity xorbench;	


architecture struct of xorbench is
	component xorgate is
		port(a,b: in bit;o: out bit);
	end component xorgate;
	
	begin
		xor0:xorgate port map(a(0),b(0),o(0));
		xor1:xorgate port map(a(1),b(1),o(1));
		xor2:xorgate port map(a(2),b(2),o(2));
		xor3:xorgate port map(a(3),b(3),o(3));
		xor4:xorgate port map(a(4),b(4),o(4));
		xor5:xorgate port map(a(5),b(5),o(5));
		xor6:xorgate port map(a(6),b(6),o(6));
		xor7:xorgate port map(a(7),b(7),o(7));
		xor8:xorgate port map(a(8),b(8),o(8));
		xor9:xorgate port map(a(9),b(9),o(9));
		xor10:xorgate port map(a(10),b(10),o(10));
		xor11:xorgate port map(a(11),b(11),o(11));
		xor12:xorgate port map(a(12),b(12),o(12));
		xor13:xorgate port map(a(13),b(13),o(13));
		xor14:xorgate port map(a(14),b(14),o(14));
		xor15:xorgate port map(a(15),b(15),o(15));
end struct;
-- norbench

entity norbench is
	
	port(
		o: in bit_VECTOR(15 downto 0);
		output: out bit_VECTOR(15 downto 0);
		z: out bit);
end entity norbench;	

architecture behaviour of norbench is
	
	begin
		z <= not (o(0) or o(1) or o(2) or o(3) or o(4) or o(5) or o(6) or o(7) or o(8) or o(9) or o(10) or o(11) or o(12) or o(13) or o(14) or o(15));
		output <= o;
		end behaviour;