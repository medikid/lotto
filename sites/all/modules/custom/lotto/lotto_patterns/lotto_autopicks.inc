<?php

function binary_padding($bin_str){
    $z = 5; $padding = '';
    if (strlen($bin_str) < $z){
	$x = $z - strlen($bin_str);

	while ($x < $z){
	    $padding .= '0';
	    $x++;
	}
	$bin_str_padded = $bin_str . $padding;
	return $bin_str_padded;
    }    
}

function binary_parser($bin_str){
    $num = base_convert($bin_str, 2, 10);
    return $num;
}

function binary_converter($num){
    $bin = base_convert($num, 10, 2);
   return $bin;
}

?>
