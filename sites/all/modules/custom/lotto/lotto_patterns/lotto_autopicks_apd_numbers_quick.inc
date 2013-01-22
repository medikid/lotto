<?php
function get_lotto_autopicks_apd_numbers_quick($lottery_name, $draw_num, $draw_num_val, $num_stops=array(5, 10, 20, 50, 100)){
    $apd_numbers = '';
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    //get_config file
	    $apd_numbers = get_lotto_autopicks_apd_numbers_quick_config($lottery_name, $num_stops);
	    $apd_numbers['draw_details']['draw_num']=$draw_num;
	    $apd_numbers['draw_details']['draw_num_val']=$draw_num_val;
	    
	    $empty_results_array = get_lotto_empty_results_array($lottery_name);
	    
	    //get lotto results
	    $val_results = db_select('lotto_keno', 'lk')->fields('lk')->condition('draw_number', $draw_num_val)->execute()->fetchAssoc();
	    $apd_numbers['lotto_results'] = $empty_results_array;
	    for($i=1; $i<=20; $i++){
		$apd_numbers['lotto_results'][$val_results['n'.$i]] = 1;
	    }	    
	    
	    //get 100 results
	    $z=100; $draw_num_first=$draw_num; $draw_num_last=$draw_num - $z;	    
	    $query_results = db_select('lotto_keno', 'lk')->fields('lk');
	    $query_results->condition('draw_number', $draw_num_first, '<=');
	    $query_results->condition('draw_number', $draw_num_last, '>=');
	    $all_results = $query_results->orderBy('draw_number', 'DESC')->execute();
	    $binary_results=array(); $diag_wins=array();
	    while($results = $all_results->fetchAssoc()){
		$num = $results['draw_number'];
		$binary_results[$num] = $empty_results_array;
		for($x=1; $x <= 20; $x++){
		    $binary_results[$num][$results['n'.$x]] = 1;
		}
	    }
	    
	    $x=0; $binary_feed_5=array();
	    while($x < 5){
		$number = $draw_num - $x;
		$binary_feed_5[$number] = $binary_results[$number];
		$x++;
	    }
	    
	    //pick autopicks
	    $lottery_patterns_5 = array();	    
	    $i = 1; $j=80; $num_draws = 5;
	    while ($i <= $j){
		$lottery_patterns_5[$i]['diag_step_up'] = lotto_pattern_diag_step_up($binary_feed_5, $draw_num, $i, $num_draws);
		$lottery_patterns_5[$i]['pillar_down'] = lotto_pattern_pillar_down($binary_feed_5, $draw_num, $i, $num_draws);
		$lottery_patterns_5[$i]['diag_step_down'] = lotto_pattern_diag_step_down($binary_feed_5, $draw_num, $i, $num_draws);
		$lottery_patterns_5[$i]['diag_und_step_up'] = lotto_pattern_diag_under_step_up($binary_feed_5, $draw_num, $i, $num_draws);
		$lottery_patterns_5[$i]['diag_und_step_down'] = lotto_pattern_diag_under_step_down($binary_feed_5, $draw_num, $i, $num_draws);
			
		$i++;
	    }    
	    $apd_numbers['autopick_nbrs'] = lotto_bets_autopick_numbers_get($lottery_name, $lottery_patterns_5);
	    
	    //pick diagwin5 apd numbers
	    $z=80; $diagwins=array(); $diag_wins_ratio=array();
	    for($a=1; $a<= $z; $a++){
		$diagwins[$a]['pillar']=array('wins'=>0,'count'=>0);
		$diagwins[$a]['forward']=array('wins'=>0,'count'=>0);
		$diagwins[$a]['backward']=array('wins'=>0,'count'=>0);
	    }
	    
	    for($x=0; $x <= 100; $x++ ){
		$current_draw_num = $draw_num - $x;
		
		for($num = 1; $num <= $z; $num++){
		    
		    $current_num = $num;
		    $diagwins[$num]['pillar']['wins'] += $binary_results[$current_draw_num][$current_num];
		    $diagwins[$num]['pillar']['count']++;
		    

		    $current_num_forward = $num + $x;		
		    if ($current_num_forward <= $z){
			$diagwins[$num]['forward']['wins'] += $binary_results[$current_draw_num][$current_num_forward];
			$diagwins[$num]['forward']['count']++;
		    } else { //SPIRAL NUMBER STARTED
			$current_num_forward_spiral = $current_num_forward % 80;
			if ($current_num_forward_spiral == 0){
			    $current_num_forward_spiral = 80;
			}

			$diagwins[$num]['forward']['wins'] += $binary_results[$current_draw_num][$current_num_forward_spiral];

		       $diagwins[$num]['forward']['count']++;		
		    } //SPIRAL NUMBERING ENDS


		    $current_num_backward = $num - $x;
		    if ($current_num_backward > 0){
			$diagwins[$num]['backward']['wins'] += $binary_results[$current_draw_num][$current_num_backward];		    
			$diagwins[$num]['backward']['count']++;
		    } else { //SPIRAL NUMBER STARTED
			$current_num_backward_spiral = 80 + ($current_num_backward % 80);
			if ($current_num_backward_spiral == 0){
			    $current_num_backward_spiral = 80;
			}

			$diagwins[$num]['backward']['wins'] += $binary_results[$current_draw_num][$current_num_backward_spiral];		    
		       $diagwins[$num]['backward']['count']++;
		    }//SPIRAL NUMBERING ENDS		
	    }
	    
	    $seq =  $x+1;
	    if( in_array( $seq, $num_stops)){
		$ratios_pillar = array(); $ratios_stepup = array(); $ratios_stepdown = array();
		foreach ( $diagwins as $num_r => $data){
		    $ratios_pillar[$num_r]= round(($data['pillar']['wins'] / $data['pillar']['count']), 3);
		    $ratios_stepup[$num_r] = round(($data['backward']['wins'] / $data['backward']['count']), 3);		    
		    $ratios_stepdown[$num_r]= round(($data['forward']['wins'] / $data['forward']['count']), 3);
		}
		arsort($ratios_pillar);
		arsort($ratios_stepup); 
		arsort($ratios_stepdown); 
		/*
		$apd_numbers['diagwin'.$seq]['pillar'] = $ratios_pillar;
		$apd_numbers['diagwin'.$seq]['stepup'] = $ratios_stepup;
		$apd_numbers['diagwin'.$seq]['stepdown'] = $ratios_stepdown;
		*/
		$x=1;
		foreach( $ratios_pillar as $num_p=>$ratio_p){		    
		    $apd_numbers['diagwin'.$seq]['pillar'][$x] = $num_p;
		    $x++;
		}
		
		$x=1;
		foreach( $ratios_stepup as $num_su=>$ratio_su){		    
		    $apd_numbers['diagwin'.$seq]['stepup'][$x] = $num_su;
		    $x++;
		}
		 
		$x=1;
		foreach( $ratios_stepdown as $num_sd=>$ratio_sd){		   
		    $apd_numbers['diagwin'.$seq]['stepdown'][$x] = $num_sd;
		    $x++;
		}		  
		
	    }	
	}
	   
	    
	    break;
    }
    return $apd_numbers;
}

function get_lotto_autopicks_apd_numbers_quick_config($lottery_name, $num_stops){
    $config=array();
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    //get_config file	    
	    $config['draw_details'] = array('draw_num'=>'', 'draw_date_time'=>'', 'draw_num_val'=>'');
	    $config['lotto_results']=array();
	    $config['autopick_nbrs'] = array('diagonal'=>array(), 'ladder'=>array());
	    foreach($num_stops as $num){
		$config['diagwin'.$num] = array(
		    'pillar'=>array(),
		    'stepup'=>array(),
		    'stepdown'=>array(),
		);
	    }  
	    break;
    }
    return $config;
}

function get_lotto_empty_results_array($lottery_name){
    $empty_results=array();
    switch($lottery_name){
	case 'lotto_max':
	    for($x=1; $x <= 49; $x++){
		$empty_results[$x]=0;
	    }
	    break;
	case 'lotto_keno':
	    for($x=1; $x <= 80; $x++){
		$empty_results[$x]=0;
	    }
	    break;
    }
    return $empty_results;
};

?>
