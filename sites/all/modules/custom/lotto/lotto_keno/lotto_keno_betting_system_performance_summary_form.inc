<?php

function get_lotto_keno_betting_system_performance_summary_form($form, $form_state){
   drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    $lottery_name = "lotto_keno";
   if (isset($draw_num)){
	$last_keno_draw_num = $draw_num;
    } else $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno") - 20;
    $last_keno_draw_num_val = $last_keno_draw_num + 1;
   
    $defaults = array(
	'no_of_draws'=>100,
	'betting_profile'=>2,
	'no_of_picks'=>10,
	'no_of_bets'=>0);
       
    $form['efficiency']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks Numbers Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['draw_number_prev']=array(
	'#type'=>'button',
	'#value'=>t('Prev'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_prev_batch',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
	'#prefix'=>'<div class="container-inline">',
    );	

    
    $form['efficiency']['draw_number']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw#: "),
	'#default_value'=> $last_keno_draw_num,
	'#size'=> 11	
    );
    
    $form['efficiency']['draw_number_next']=array(
	'#type'=>'button',
	'#value'=>t('Next'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_next_batch',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    ); 
    
    $form['efficiency']['number_of_draws']=array(
	'#type'=>  'textfield',
	'#title'=>t("Number of Draws#: "),
	'#default_value'=>$defaults['no_of_draws'],
	'#size'=> 11	
    );
    
    $form['efficiency']['refresh']=array(
	'#type'=>'button',
	'#value'=>t('Refresh'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_refresh_batch',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
	'#suffix'=>'</div>'
    );
    
     
   $form['efficiency']['betting_profile']=array(
	'#type'=>  'select',
	'#title'=>t("Betting Profile: "),
	'#default_value'=>$defaults['betting_profile'],
	'#options'=>array(
	    0=>t("Select Profile"),
	    1=>t("Exclude Current Results(~20)"),
	    2=>t("Exclude Current-Last Results(~35)")
	),
       '#prefix'=>'<div class="container-inline">'
    );
    
    $form['efficiency']['number_of_picks']=array(
	'#type'=>  'select',
	'#title'=>t("Picks#: "),
	'#default_value'=> $defaults['no_of_picks'],
	'#options'=>array(
	    0=>t("Select Profile"),
	    1=>t("1s"),
	    2=>t("2s"),
	    3=>t("3s"),
	    4=>t("4s"),
	    5=>t("5s"),
	    6=>t("6s"),
	    7=>t("7s"),
	    8=>t("8s"),
	    9=>t("9s"),
	    10=>t("10s")
	),
	'#prefix'=>'&nbsp &nbsp'
    );
    $form['efficiency']['number_of_bets']=array(
	'#type'=>  'textfield',
	'#title'=>t("Bets#: "),
	'#default_value'=> $defaults['no_of_bets'],
	'#size'=>3,
	'#prefix'=>'&nbsp &nbsp',
	'#suffix'=>'</div>'
    );
    
        
    $form['efficiency']['betting_system_performance']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Betting System:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_betting_system_wrapper" >',
	'#suffix'=>'</div>'
    );
    
 
    $form['efficiency']['betting_system_performance']['grid']=array(
	'#markup'=>lotto_keno_betting_system_performance_summary_grid_create($lottery_name, $last_keno_draw_num, $defaults['no_of_draws'], $defaults['betting_profile'], $defaults['no_of_picks'])
    );
    
    
    return $form;
}

function ajx_numbers_draw_number_prev_batch($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_num = $form_state['values']['draw_number'];
    $number_of_draws = $form_state['values']['number_of_draws'];
    $draw_num_prev_batch = $draw_num - $number_of_draws;
    
    $betting_profile=$form_state['values']['betting_profile'];
    $number_of_picks=$form_state['values']['number_of_picks'];
    $number_of_bets=$form_state['values']['number_of_bets'];
    
    $betting_system_performance_grid = lotto_keno_betting_system_performance_summary_grid_create($lottery_name, $draw_num_prev_batch, $number_of_draws, $betting_profile, $number_of_picks, $number_of_bets);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_prev_batch;
    $form['efficiency']['betting_system_performance']['grid']['#markup'] = $betting_system_performance_grid;
    
    return $form['efficiency'];
}

function ajx_numbers_draw_number_next_batch($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_num = $form_state['values']['draw_number'];
    $number_of_draws = $form_state['values']['number_of_draws'];
    $draw_num_next_batch = $draw_num + $number_of_draws;
    
    $betting_profile=$form_state['values']['betting_profile'];
    $number_of_picks=$form_state['values']['number_of_picks'];
    $number_of_bets=$form_state['values']['number_of_bets'];
    
    $betting_system_performance_grid = lotto_keno_betting_system_performance_summary_grid_create($lottery_name, $draw_num_next_batch, $number_of_draws, $betting_profile, $number_of_picks, $number_of_bets);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_next_batch;
    $form['efficiency']['betting_system_performance']['grid']['#markup'] = $betting_system_performance_grid;
    
    return $form['efficiency'];    
}

function ajx_numbers_draw_number_refresh_batch($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_num = $form_state['values']['draw_number'];
    $number_of_draws = $form_state['values']['number_of_draws'];
    
    $betting_profile=$form_state['values']['betting_profile'];
    $number_of_picks=$form_state['values']['number_of_picks'];
    $number_of_bets=$form_state['values']['number_of_bets'];
    
    $betting_system_performance_grid = lotto_keno_betting_system_performance_summary_grid_create($lottery_name, $draw_num, $number_of_draws, $betting_profile, $number_of_picks, $number_of_bets);
        
    $form['efficiency']['betting_system_performance']['grid']['#markup'] = $betting_system_performance_grid;
    
    return $form['efficiency'];    
}


function lotto_keno_betting_system_performance_summary_grid_create($lottery_name, $draw_num, $no_of_draws, $betting_profile, $no_of_picks, $number_of_bets=0){
    $betting_system_performance_summary_grid=array();
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $header = "<table class=\"betting_system_performance_grid\" ><tbody>";
	    
	    $label1 = "<tr>";
	    $label1 .= "<th>Labels</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin5</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin10</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin20</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin50</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin100</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >RatioSum</th>";
	    $label1 .= "</tr>";
	    
	    $label2 = "<tr>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Spent</th>";
	    $label2 .= "<th>Won</th>";
	    $label2 .= "<th>Profit</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Spent</th>";
	    $label2 .= "<th>Won</th>";
	    $label2 .= "<th>Profit</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Spent</th>";
	    $label2 .= "<th>Won</th>";
	    $label2 .= "<th>Profit</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Spent</th>";
	    $label2 .= "<th>Won</th>";
	    $label2 .= "<th>Profit</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Spent</th>";
	    $label2 .= "<th>Won</th>";
	    $label2 .= "<th>Profit</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Spent</th>";
	    $label2 .= "<th>Won</th>";
	    $label2 .= "<th>Profit</th>";
	    $label2 .= "</tr>";
	    
	    
	    $body = ""; 
	    $overall_empty=array('diagwin5'=>0, 'diagwin10'=>0, 'diagwin20'=>0, 'diagwin50'=>0, 'diagwin100'=>0);
	    $overall_spent=$overall_empty; $overall_won=$overall_empty;
	    
	    for($x=0; $x < $no_of_draws; $x++){
		$draw_num_current = $draw_num - $x;
		$betting_system_performance_summary =lotto_keno_betting_system_performance_summary($lottery_name, $draw_num_current, $betting_profile, $no_of_picks, $number_of_bets);
		
		$body .= "<tr>";
		
		$body .= "<th>".date('d-M-Y h:i', $betting_system_performance_summary['draw_details']['draw_date_time'])."</th>";
		$body .=  "<th></th>";
		$body .= "<td>".$betting_system_performance_summary['diagwin5']['total_spent']."</td>";
		$body .= "<td>".$betting_system_performance_summary['diagwin5']['total_won']."</td>";
		$body .= ($betting_system_performance_summary['diagwin5']['total_profit'] > 0) ? "<td class=\"green\" >" : "<td class=\"red\" >";
		$body .= $betting_system_performance_summary['diagwin5']['total_profit']."</td>";
		
		$overall_spent['diagwin5'] += $betting_system_performance_summary['diagwin5']['total_spent'];
		$overall_won['diagwin5'] += $betting_system_performance_summary['diagwin5']['total_won'];
		
		$body .=  "<th></th>";
		$body .= "<td>".$betting_system_performance_summary['diagwin10']['total_spent']."</td>";
		$body .= "<td>".$betting_system_performance_summary['diagwin10']['total_won']."</td>";
		$body .= ($betting_system_performance_summary['diagwin10']['total_profit'] > 0) ? "<td class=\"green\" >" : "<td class=\"red\" >";
		$body .= $betting_system_performance_summary['diagwin10']['total_profit']."</td>";
		
		$overall_spent['diagwin10'] += $betting_system_performance_summary['diagwin10']['total_spent'];
		$overall_won['diagwin10'] += $betting_system_performance_summary['diagwin10']['total_won'];
		
		$body .=  "<th></th>";
		$body .= "<td>".$betting_system_performance_summary['diagwin20']['total_spent']."</td>";
		$body .= "<td>".$betting_system_performance_summary['diagwin20']['total_won']."</td>";
		$body .= ($betting_system_performance_summary['diagwin20']['total_profit'] > 0) ? "<td class=\"green\" >" : "<td class=\"red\" >";
		$body .= $betting_system_performance_summary['diagwin20']['total_profit']."</td>";
		
		$overall_spent['diagwin20'] += $betting_system_performance_summary['diagwin20']['total_spent'];
		$overall_won['diagwin20'] += $betting_system_performance_summary['diagwin20']['total_won'];
		
		$body .=  "<th></th>";
		$body .= "<td>".$betting_system_performance_summary['diagwin50']['total_spent']."</td>";
		$body .= "<td>".$betting_system_performance_summary['diagwin50']['total_won']."</td>";
		$body .= ($betting_system_performance_summary['diagwin50']['total_profit'] > 0) ? "<td class=\"green\" >" : "<td class=\"red\" >";
		$body .= $betting_system_performance_summary['diagwin50']['total_profit']."</td>";
		
		$overall_spent['diagwin50'] += $betting_system_performance_summary['diagwin50']['total_spent'];
		$overall_won['diagwin50'] += $betting_system_performance_summary['diagwin50']['total_won'];
		
		$body .=  "<th></th>";
		$body .= "<td>".$betting_system_performance_summary['diagwin100']['total_spent']."</td>";
		$body .= "<td>".$betting_system_performance_summary['diagwin100']['total_won']."</td>";
		$body .= ($betting_system_performance_summary['diagwin100']['total_profit'] > 0) ? "<td class=\"green\" >" : "<td class=\"red\" >";
		$body .= $betting_system_performance_summary['diagwin100']['total_profit']."</td>";
		
		$overall_spent['diagwin100'] += $betting_system_performance_summary['diagwin100']['total_spent'];
		$overall_won['diagwin100'] += $betting_system_performance_summary['diagwin100']['total_won'];
		
		$body .=  "<th></th>";
		$body .= "<td></td>";
		$body .= "<td></td>";
		$body .= "<td></td>";
		
		$body .="</tr>";
	    }
	    
	    $body .="<tr><th>Overall Total</th>";
	    foreach($overall_spent as $overall_cat=>$spent){
		$body .="<th></th>";
		$body .= "<td class\"grey\" >". $spent ."</td>";
		$body .= "<td class\"grey\" >".$overall_won[$overall_cat]."</td>";
		$overall_profit = $overall_won[$overall_cat] - $spent;
		$body .= ($overall_profit > 0) ? "<td class=\"green\" >" : "<td class=\"red\" >";
		$body .= $overall_profit."</td>";
	    }
	    
	    $body .= "<th></th>";
	    $body .= "<td></td><td></td><td></td>";	    
	    $body ."</tr>";
	    
	   $footer = "</tbody></table>";
	   
	   $betting_system_performance_summary_grid = $header . $label1 . $label2 . $body. $footer;
	    break;
    }
    return $betting_system_performance_summary_grid;
}

function lotto_keno_betting_system_performance_summary($lottery_name, $draw_num, $betting_profile, $no_of_picks, $number_of_bets){
    $betting_system_performance_summary=array();
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    
	    $apd_numbers = get_lotto_autopicks_apd_numbers_quick($lottery_name, $draw_num, $draw_num+1);
	    $betting_system_performance_summary['draw_details']=$apd_numbers['draw_details'];
	    $bets_performance = lotto_keno_betting_system_bets_performance_summary_quick($lottery_name, $apd_numbers, $betting_profile, $no_of_picks, $number_of_bets);
	    
	    foreach($bets_performance as $diagwin_cat=>$data_diag){
		$total_spent = 0; $total_won = 0; $total_profit = 0;
		foreach($data_diag as $cat=>$summary){
		    $spent = $summary['bets'];
		    $won = array_sum( $summary['win'] );		    
		    $total_spent += $spent;
		    $total_won += $won;		    
		}
		    $total_profit += $total_won - $total_spent;
		    $betting_system_performance_summary[$diagwin_cat]['total_spent']=$total_spent;
		    $betting_system_performance_summary[$diagwin_cat]['total_won']=$total_won;
		    $betting_system_performance_summary[$diagwin_cat]['total_profit']=$total_profit;
	    }	    
	    
	    break;
    }
    return $betting_system_performance_summary;
}
?>
