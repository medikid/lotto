<?php

/*
 * Excludes last won numbers as unlucky numbers
 */
function profile_exclude_currently_won_numbers($lottery_name, $draw_num){
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $results = lotto_keno_result_by_draw_num($draw_num);
	    $x=1;$y=20; $numbers=array();
	    while($x <= $y){
		array_push($numbers, $results['n'.$x]);
		$x++;
	    }
	    break;
    }
    return $numbers;
}


function profile_exclude_current_n_last_won_numbers($lottery_name, $draw_num){
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $results = lotto_keno_result_by_draw_num($draw_num);
	    $x=1;$y=20; $numbers=array();
	    while($x <= $y){
		array_push($numbers, $results['n'.$x]);
		$x++;
	    }
	    
	    $last_results =  lotto_keno_result_by_draw_num($draw_num - 1);
	    $x=1;$y=20;
	    while($x <= $y){
		$num = $last_results['n'.$x];
		if ( !in_array($num, $numbers)){
		    array_push($numbers, $num);
		}
		$x++;
	    }    
	    break;
    }
    return $numbers;
}

function lotto_bets_group_sets($group_of_numbers, $set_of){
    $bets=array();
    $x=0; $y=0;
    foreach($group_of_numbers as $number){
	if($x < $set_of){
	    $bets[$y][$x] =  $number;
	    $x++;
	} else {
	    $x=0;
	    $y++;
	    $bets[$y][$x] =  $number;
	    $x++;
	}
    }
    return $bets;
}

?>
