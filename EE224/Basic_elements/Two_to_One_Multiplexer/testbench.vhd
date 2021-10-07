entity testbench is
end testbench;
architecture tb of testbench is
	signal x,y,z : bit; -- inputs
	signal output : bit; -- output
component mux is
	port(i0,i1,s: in bit;o: out bit);
end component;
	begin
	-- Connecting test bench signals with mux.vhd
	dut_instance: mux
	port map (i0 => x, i1 => y, s => z, o => output);
	process-- inputs
		begin
			x <= '0';
			y <= '0';
			z <= '0';
			wait for 5 ns;
			x <= '0';
			y <= '0';
			z <= '1';
			wait for 5 ns;
			x <= '0';
			y <= '1';
			z <= '1';
			wait for 5 ns;
			x <= '0';
			y <= '1';
			z <= '0';
			wait for 5 ns;
			x <= '1';
			y <= '0';
			z <= '1';
			wait for 5 ns;
			x <= '1';
			y <= '0';
			z <= '0';
			wait for 5 ns;
			x <= '1';
			y <= '1';
			z <= '0';
			wait for 5 ns;
			x <= '1';
			y <= '1';
			z <= '1';
			wait for 5 ns;
	end process;
end tb ;