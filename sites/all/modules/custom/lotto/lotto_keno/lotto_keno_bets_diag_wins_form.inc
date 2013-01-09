<?php

function get_lotto_keno_bets_diag_wins_form($form, &$form_state){
    
    $form = array();
	
    $form['bets'] = array(
	    '#type'=>'fieldset',
	    '#title'=>t('Bets From Diag Wins'),
	    '#collapsible'=>true,
	    '#collapsed'=>false
	);
    	$form['bets']['draw_number']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Draw Number: '),
	    '#default_value'=>'',
	    '#size'=>20,
	    '#prefix'=>'<div class="container-inline">',
	    '#suffix'=>'&nbsp &nbsp'
	);
	
	$form['bets']['bets_notes']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Notes: '),
	    '#default_value'=>'',
	    '#size'=>200,
	    '#suffix'=>'</div><br>',
	);
	
	
	
	$form['bets']['number_of_draws']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Number of subsequent Draws to Play: '),
	    '#default_value'=>'',
	    '#size'=>20,
	    '#prefix'=>'<div class="container-inline">',
	    '#suffix'=>'&nbsp &nbsp'
	);
	
	$form['bets']['play_as']=array(
	    '#type'=>'select',
	    '#title'=>t('Play as: '),
	    '#options'=>array(
		1=>'All Numbers',
		2=>'Combinations'
	    ),
	    '#default_value'=>'1',
	    '#suffix'=>'&nbsp &nbsp'
	);
	
	$form['bets']['combinations_of']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Number of Combinations: '),
	    '#default_value'=>'',
	    '#size'=>4,
	    '#states'=> array(
		    'visible' => array(':input[name="play_as"]' => array('value' => '2'),
				    ),
		),
	    '#suffix'=>'</div><br>',
	);
	
	$form['bets']['diag_step_up']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Diag Step-Up Numbers: '),
	    '#default_value'=>'',
	    '#size'=>200,
	    '#prefix'=>'<div class="container-inline">',
	    '#suffix'=>'</div><br>',
	);
	$form['bets']['diag_step_down']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Diag Step-Up Numbers: '),
	    '#default_value'=>'',
	     '#size'=>200,
	    '#prefix'=>'<div class="container-inline">',
	    '#suffix'=>'</div><br>',
	);
	$form['bets']['ladder']=array(
	    '#type'=>'textfield',
	    '#title'=>t('Ladder(Vertical): '),
	    '#default_value'=>'',
	     '#size'=>200,
	    '#prefix'=>'<div class="container-inline">',
	    '#suffix'=>'</div><br>',
	);
	
	$form['diag_wins']['bets_diag_wins'] = array(
	'#type'=>'button',
	'#value'=>t('Place Bets'),
	'#ajax'=>array(
	    'callback' => 'ajx_keno_bets_diag_wins',
	    'wrapper'=>'ajx_keno_bets_diag_wins_wrapper',
	    'method'=>'replace'
	),
	'#prefix'=>'<div class="container-inline">',
	    '#suffix'=>'&nbsp &nbsp'
	    
    );
    
	$form['diag_wins']['review_bets_diag_wins'] = array(
	'#type'=>'button',
	'#value'=>t('Review Bets'),
	'#ajax'=>array(
	    'callback' => 'ajx_keno_bets_diag_wins_review',
	    'wrapper'=>'ajx_keno_bets_diag_wins_wrapper',
	    'method'=>'replace'
	),
	'#suffix'=>'</div>'
    );
	
    $form['diag_wins']['bets_review_grid']= array(
	'#markup'=>'',
	'#prefix'=>'<br><div id="ajx_keno_bets_diag_wins_wrapper">',
	'#suffix'=>'</div>',
    );
    
    return $form;
   
   
}

function ajx_keno_bets_diag_wins($form, $form_state){
    
     lotto_keno_place_diag_wins_bets($form, $form_state);
    
    
    
    $form['diag_wins']['bets_review_grid']['#markup'] = "Bets Placed";
    return $form['diag_wins']['bets_review_grid'];
}

function lotto_keno_place_diag_wins_bets($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $bets_notes = $form_state['values']['bets_notes'];
    $num_of_draws = $form_state['values']['number_of_draws'];
    $play_as = $form_state['values']['play_as'];
    $no_of_combos = $form_state['values']['combinations_of'];
    $diag_step_up = $form_state['values']['diag_step_up'];
    $diag_step_down = $form_state['values']['diag_step_down'];
    $ladder = $form_state['values']['ladder'];
    
    switch($play_as){
	case 1:
	    $bet_numbers =array();
	    $diag_step_up_nums = array();
	    $diag_step_down_nums = array();
	    $ladder_nums = array();
	    
		if( strlen($diag_step_up) > 0){
		$dsu_nums = explode(" ", $diag_step_up);		
		    foreach($dsu_nums as $ind=>$values){
			if (strlen(trim($values)) > 0){
			    array_push($diag_step_up_nums, trim($values));
		       } 
		    }
		}
		
		if( strlen($diag_step_down) > 0){
		$dsd_nums = explode(" ", $diag_step_down);
		    foreach($dsd_nums as $ind=>$values){
			if (strlen(trim($values)) > 0){
			    array_push($diag_step_down_nums, trim($values));
		       }
		     }
		}
		
		if( strlen($ladder) > 0){
		$ld_nums = explode(" ", $ladder);		
		    foreach($ld_nums as $ind=>$values){
			if (strlen(trim($values)) > 0){
			    array_push($ladder_nums, trim($values));
		       }
		    }
		}
		
		if ( (count($diag_step_up_nums) + count($diag_step_down_nums) + count($ladder_nums)) > 10 ){
		   // array_chunk($bet_numbers, 10);
		} else {
			$bets_config=array(
			  'lkbid'=>null,
			    'uid'=>1,
			    'live_bets_flag'=>0,
			    'live_bets_done'=>0,
			    'picks'=>count($bet_numbers),
			    'bonus'=>null
			);		     
		
		
		    for($x = 1; $x < $num_of_draws; $x++ ){
			$bets = $bets_config;
			$current_draw_number =   $draw_num + $x;
			$bets['draw_number']=$current_draw_number;
			
			$i=1; $j = 10;
			foreach ($diag_step_up_nums as $nums){
			    $bet_number = $nums + $x;
			    if ($bet_number <= 80){
				$bets['b'.$i] = $bet_number;
				$i++;
			    }
			}
			
			foreach ($diag_step_down_nums as $nums){
			    $bet_number = $nums - $x;
			    if ($bet_number > 0){
				$bets['b'.$i] = $bet_number;
				$i++;
			    }
			}
			
			foreach ($ladder_nums as $nums){
			    $bet_number = $nums;
			    if ($bet_number <= 80){
				$bets['b'.$i] = $bet_number;
				$i++;
			    }
			}
			
			
			$inserted = db_insert('lotto_keno_bets')
					    ->fields($bets)
					    ->execute();

			if( strlen($bets_notes) > 0){
				$insert_notes = db_insert('lotto_keno_bets_notes')
					    ->fields( array('lkbnid'=>null, 'lkbid'=>$inserted, 'lkb_notes'=>$bets_notes) )
					    ->execute();
			    }		
		    }
		}
	    break;
	case 2:
	    break;
	
    }
}

?>
