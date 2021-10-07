library IEEE;
use IEEE.std_logic_1164.all;
entity ALU is
	port(s0,s1: in bit;
	a: in bit_VECTOR(15 downto 0);
	b: in bit_VECTOR(15 downto 0);
	o: out bit_VECTOR(15 downto 0);
	z,carry: out bit);
end entity ALU;
architecture struct of ALU is
	signal nb : bit_vector(15 downto 0);
	signal sum : bit_vector(15 downto 0);
	signal nandall : bit_vector(15 downto 0);
	signal xorall : bit_vector(15 downto 0);
	signal fin : bit_vector(15 downto 0);
	signal s1b,C : bit ;
	
	component adder is
		port(
			a: in bit_VECTOR(15 downto 0);
			b: in bit_VECTOR(15 downto 0);
			cr0:in bit;
			o: out bit_VECTOR(15 downto 0);
			carry: out bit);
	end component;
	component inverter is
		port(
			b: in bit_VECTOR(15 downto 0);
			s0: in bit;
			o: out bit_VECTOR(15 downto 0));
	end component;
	component norbench is
		port(
			o: in bit_VECTOR(15 downto 0);
			output: out bit_VECTOR(15 downto 0);
			z: out bit);
	end component;	
	component nandbench is
		port(
			a: in bit_VECTOR(15 downto 0);
			b: in bit_VECTOR(15 downto 0);
			o: out bit_VECTOR(15 downto 0));
	end component;
	component xorbench is
		port(
			a: in bit_VECTOR(15 downto 0);
			b: in bit_VECTOR(15 downto 0);
			o: out bit_VECTOR(15 downto 0));
	end component;
	component muxbench is
		port(s0,s1: in bit;
			a: in bit_VECTOR(15 downto 0);
			b: in bit_VECTOR(15 downto 0);
			c: in bit_VECTOR(15 downto 0);
			d: in bit_VECTOR(15 downto 0);
			o: out bit_VECTOR(15 downto 0));
	end component muxbench;
	
	component andgate is
	   port(a,b: in bit ; o : out bit);
	end component andgate;
	
	component notgate is
	   port( a : in bit ; o : out bit);
	end component notgate;
	
	
	begin
		mux16:muxbench port map(s0,s1,sum,sum,nandall,xorall,fin);
		adder16:adder port map(a,nb,s0,sum,C);
		inverter16:inverter port map(b,s0,nb);
		nandbench16:nandbench port map(a,b,nandall);
		xorbench16:xorbench port map(a,b,xorall);
		norall:norbench port map(fin,o,z);
		
		notgate_final : notgate port map(s1,s1b);
		andgate_final : andgate port map(s1b,C,carry);
		
		
		
end struct;
