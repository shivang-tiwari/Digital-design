entity testbench is
end testbench;
architecture tb of testbench is
	signal w,x,y,z : bit; -- inputs
	signal o : bit; -- output
component four_input_xor is
	port(A,B,C,D: in bit;F: out bit);
end component;
	begin
	-- Connecting test bench signals with four_input_xor.vhd
	dut_instance: four_input_xor
	port map (A => w, B => x, C => y, D => z, F => o);
	process-- inputs
		begin
			w <= '0';
			x <= '0';
			y <= '0';
			z <= '0';
			wait for 5 ns;
			w <= '0';
			x <= '0';
			y <= '0';
			z <= '1';
			wait for 5 ns;
			w <= '0';
			x <= '0';
			y <= '1';
			z <= '1';
			wait for 5 ns;
			w <= '0';
			x <= '0';
			y <= '1';
			z <= '0';
			wait for 5 ns;
			w <= '0';
			x <= '1';
			y <= '0';
			z <= '1';
			wait for 5 ns;
			w <= '0';
			x <= '1';
			y <= '0';
			z <= '0';
			wait for 5 ns;
			w <= '0';
			x <= '1';
			y <= '1';
			z <= '0';
			wait for 5 ns;
			w <= '0';
			x <= '1';
			y <= '1';
			z <= '1';
			wait for 5 ns;
			w <= '1';
			x <= '0';
			y <= '0';
			z <= '1';
			wait for 5 ns;
			w <= '1';
			x <= '0';
			y <= '0';
			z <= '0';
			wait for 5 ns;
			w <= '1';
			x <= '0';
			y <= '1';
			z <= '0';
			wait for 5 ns;
			w <= '1';
			x <= '0';
			y <= '1';
			z <= '1';
			wait for 5 ns;
			w <= '1';
			x <= '1';
			y <= '0';
			z <= '0';
			wait for 5 ns;
			w <= '1';
			x <= '1';
			y <= '0';
			z <= '1';
			wait for 5 ns;
			w <= '1';
			x <= '1';
			y <= '1';
			z <= '1';
			wait for 5 ns;
			w <= '1';
			x <= '1';
			y <= '1';
			z <= '0';
			wait for 5 ns;
	end process;
end tb ;
