<?php

function binary_padding($bin_str){
    $z = 5; $padding = '';
    if (strlen($bin_str) < $z){
	$x = $z - strlen($bin_str);

	while ($x > 0){
	    $padding .= '0';
	    $x--;
	}	
    } 
    $bin_str_padded = $bin_str . $padding;
    return $bin_str_padded;
}

function binary_parse($bin_str){
    $num = base_convert(binary_padding($bin_str), 2, 10);
    return $num;
}

function binary_convert($num){
    $bin = base_convert($num, 10, 2);
   return $bin;
}

function autopick_rules(){
    /*
     Bin= 16-8-4-2-1
     Diag = 11000(24) to 11111(31)
     DiagLadder = 01010(10) or 01011(11)
     
     */
}

function lotto_bets_autopick_config($lottery_name){
    $autopick_config = array();
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $x=1; $y=80;
	    while ($x <= $y){
		$autopick_config[$x] = array();
		$x++;
	    }	    
	    break;
    }
    return $autopick_config;
}

function lotto_bets_autopick($lottery_name, $lottery_draw_num){
    $autopicks_config= lotto_bets_autopick_config($lottery_name);
    $autopicks = array('diagonal'=>array(), 'pillar'=>array(), 'ladder'=>array(),'sequence'=>array(),'previous_trend'=>array() );
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $x=1; $y=80; $num_draws = 5;	    
	    $patterns = lotto_patterns_create($lottery_name, $lottery_draw_num, $num_draws);
	    
	    while ($x <= $y){
		
		//Rules
		if (binary_parse($patterns[$x]['diag_step_up']) >= 24){
		    if ($x < $y){
			$autopicks_config[$x+1] = array('diag_step_up'=>$patterns[$x]['diag_step_up']);
			if(!in_array($x+1, $autopicks['diagonal'])){
			    array_push($autopicks['diagonal'], $x+1);
			}
		    }
		}
		
		if (binary_parse($patterns[$x]['diag_step_up']) == 10 || binary_parse($patterns[$x]['diag_step_up']) == 11){
		    if ($x < $y){
			$autopicks_config[$x+1] = array('diag_step_up_ladder'=>$patterns[$x]['diag_step_up']);
			array_push($autopicks['ladder'], $x+1);
		    }
		}
		
		if (binary_parse($patterns[$x]['diag_step_down']) >= 24){
		    if ($x > 1){
			$autopicks_config[$x-1] = array('diag_step_down'=>$patterns[$x]['diag_step_down']);
			array_push($autopicks['diagonal'], $x-1);
		    }
		} 
		
		if (binary_parse($patterns[$x]['diag_step_down']) == 10 || binary_parse($patterns[$x]['diag_step_down']) == 11){
		    if ($x > 1){
			$autopicks_config[$x-1] = array('diag_step_down_ladder'=>$patterns[$x]['diag_step_down']);
			array_push($autopicks['ladder'], $x-1);
		    }
		}
		
		if (binary_parse($patterns[$x]['pillar_down']) == 10 || binary_parse($patterns[$x]['pillar_down']) == 11){
		    	$autopicks_config[$x] = array('pillar_ladder'=>$patterns[$x]['pillar_down']);
			array_push($autopicks['ladder'], $x);
		}
		
		$x++;
	    }    
	    
	    break;
    }
    
    $autopicks['diagonal'] = array_unique($autopicks['diagonal']);
    $autopicks['pillar'] = array_unique($autopicks['pillar']);
    $autopicks['ladder'] = array_unique($autopicks['ladder']);
    $autopicks['sequence'] = array_unique($autopicks['sequence']);
    $autopicks['previous_trend'] = array_unique($autopicks['previous_trend']);
    
    return $autopicks;
}

?>
