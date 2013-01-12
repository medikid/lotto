<?php

function get_lotto_keno_autopicks_efficiency_report_form($form, $form_state){
    
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno");
    $num_of_draws_default = 15;
    
    $form['efficiency']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['draw_number']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw#: "),
	'#default_value'=> $last_keno_draw_num,
	'#size'=> 11,
	'#prefix'=>'<div class="container-inline" >'
    );
    
    $form['efficiency']['num_of_draws']=array(
	'#type'=>  'textfield',
	'#title'=>t("Number of Draws: "),
	'#default_value'=> $num_of_draws_default,
	'#size'=> 11	
    );
    $form['efficiency']['review_efficiency']=array(
	'#type'=>'button',
	'#value'=>t('Refresh'),
	'#ajax'=>array(
	    'callback' => 'ajx_autopicks_efficiency_report',
	    'wrapper'=>'ajx_autopicks_efficiency_report_wrapper',
	    'method'=>'replace'
	),
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['efficiency_report']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Efficiency Report:"),
	'#collapsible'=>true,
	'#collapsed'=>false
    );
    
    $form['efficiency']['efficiency_report']['report'] = array(
	'#markup'=>'',//get_lotto_patterns_autopicks_efficiency_report("lotto_keno", 1563918, 1563919, 10),
	'#prefix'=>'<div id="ajx_autopicks_efficiency_report_wrapper" >',
	'#suffix'=>'</div>'
    );
    return $form;
}



function lotto_patterns_autopicks_efficiency_report_create($lottery_name, $draw_num, $num_of_draws=50, $draw_num_val=null){
       
    
    
}

function lotto_patterns_autopicks_efficiency_report_data($lottery_name, $draw_num, $draw_num_val){
    $report_numbers = get_autopicks_efficiency_report_numbers($lottery_name, $draw_num, $draw_num_val);
    $report_data = array();
    $report_data['draw_details'] = $report_numbers['draw_details'];
    
    $lotto_results = $report_numbers['lotto_results'];
    /*********************AUTOPICKs***********************************/
    $autopicks = $report_numbers['autopick_nbrs'];    
    
    $report_data['autopicks']['diagonal']['match'] = 0;
    $report_data['autopicks']['diagonal']['count'] = count($autopicks['diagonal']);    
    foreach( $autopicks['diagonal'] as $num_d){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['diagonal']['match']++;
	}
    }
    
    $report_data['autopicks']['ladder']['match'] = 0;
    $report_data['autopicks']['ladder']['count'] = count($autopicks['ladder']);    
    foreach( $autopicks['ladder'] as $num_l){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['ladder']['match']++;
	}
    }
    /*********************DIAGWIN-5***********************************/
    $diagwin5 = $report_numbers['diagwin5'];
    
    $report_data['diagwin5']['stepup']['match'] = 0;
    $report_data['diagwin5']['stepup']['count'] = count($diagwin5['stepup']);    
    foreach( $diagwin5['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin5']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin5']['stepdown']['match'] = 0;
    $report_data['diagwin5']['stepdown']['count'] = count($diagwin5['stepdown']);    
    foreach( $diagwin5['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin5']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin5']['z1updown']['match'] = 0;
    $report_data['diagwin5']['z1updown']['count'] = count($diagwin5['z1updown']);    
    foreach( $diagwin5['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin5']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin5']['z2updown']['match'] = 0;
    $report_data['diagwin5']['z2updown']['count'] = count($diagwin5['z2updown']);    
    foreach( $diagwin5['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin5']['z2updown']['match']++;
	}
    }
    /********************DIAGWIN-10*******************************/
  $diagwin10 = $report_numbers['diagwin10'];
    
    $report_data['diagwin10']['stepup']['match'] = 0;
    $report_data['diagwin10']['stepup']['count'] = count($diagwin10['stepup']);    
    foreach( $diagwin10['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin10']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin10']['stepdown']['match'] = 0;
    $report_data['diagwin10']['stepdown']['count'] = count($diagwin10['stepdown']);    
    foreach( $diagwin10['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin10']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin10']['z1updown']['match'] = 0;
    $report_data['diagwin10']['z1updown']['count'] = count($diagwin10['z1updown']);    
    foreach( $diagwin10['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin10']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin10']['z2updown']['match'] = 0;
    $report_data['diagwin10']['z2updown']['count'] = count($diagwin10['z2updown']);    
    foreach( $diagwin10['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin10']['z2updown']['match']++;
	}
    }
     /********************DIAGWIN-20*******************************/
  $diagwin20 = $report_numbers['diagwin20'];
    
    $report_data['diagwin20']['stepup']['match'] = 0;
    $report_data['diagwin20']['stepup']['count'] = count($diagwin20['stepup']);    
    foreach( $diagwin20['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin20']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin20']['stepdown']['match'] = 0;
    $report_data['diagwin20']['stepdown']['count'] = count($diagwin20['stepdown']);    
    foreach( $diagwin20['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin20']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin20']['z1updown']['match'] = 0;
    $report_data['diagwin20']['z1updown']['count'] = count($diagwin20['z1updown']);    
    foreach( $diagwin20['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin20']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin20']['z2updown']['match'] = 0;
    $report_data['diagwin20']['z2updown']['count'] = count($diagwin20['z2updown']);    
    foreach( $diagwin20['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin20']['z2updown']['match']++;
	}
    }
        /********************DIAGWIN-50*******************************/
  $diagwin50 = $report_numbers['diagwin50'];
    
    $report_data['diagwin50']['stepup']['match'] = 0;
    $report_data['diagwin50']['stepup']['count'] = count($diagwin50['stepup']);    
    foreach( $diagwin50['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin50']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin50']['stepdown']['match'] = 0;
    $report_data['diagwin50']['stepdown']['count'] = count($diagwin50['stepdown']);    
    foreach( $diagwin50['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin50']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin50']['z1updown']['match'] = 0;
    $report_data['diagwin50']['z1updown']['count'] = count($diagwin50['z1updown']);    
    foreach( $diagwin50['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin50']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin50']['z2updown']['match'] = 0;
    $report_data['diagwin50']['z2updown']['count'] = count($diagwin50['z2updown']);    
    foreach( $diagwin50['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin50']['z2updown']['match']++;
	}
    }
    
          /********************DIAGWIN-100*******************************/
  $diagwin100 = $report_numbers['diagwin100'];
    
    $report_data['diagwin100']['stepup']['match'] = 0;
    $report_data['diagwin100']['stepup']['count'] = count($diagwin100['stepup']);    
    foreach( $diagwin100['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin100']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin100']['stepdown']['match'] = 0;
    $report_data['diagwin100']['stepdown']['count'] = count($diagwin100['stepdown']);    
    foreach( $diagwin100['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin100']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin100']['z1updown']['match'] = 0;
    $report_data['diagwin100']['z1updown']['count'] = count($diagwin100['z1updown']);    
    foreach( $diagwin100['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin100']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin100']['z2updown']['match'] = 0;
    $report_data['diagwin100']['z2updown']['count'] = count($diagwin100['z2updown']);    
    foreach( $diagwin100['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin100']['z2updown']['match']++;
	}
    }
     
    return $report_data; 
}

function get_autopicks_efficiency_report_numbers($lottery_name, $draw_num, $draw_num_val){
    $draw = lotto_keno_result_by_draw_num($draw_num);
    
    
    $draw_val = lotto_keno_result_by_draw_num($draw_num_val);
    
    $draw_results_val=array();
    for($i=1; $i <= 20; $i++){
	array_push($draw_results_val, $draw_val['n'.$i]);
    }
    
    $autopicks = lotto_bets_autopick($lottery_name, $draw_num);
    $autopicks_efficiency_report_numbers = array(
	'draw_details'=>array(
	    'draw_num'=>$draw_num,
	    'draw_time'=>date('h:i', $draw['draw_date']),
	    'draw_num_val'=>$draw_num_val
	    ),
	'lotto_results'=>$draw_results_val,
	'autopick_nbrs'=>array(
	    'diagonal'=>$autopicks['diagonal'],
	    'ladder'=>$autopicks['ladder']
	    ),
	'diagwin5'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 5, 10),
	'diagwin10'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 10, 10),
	'diagwin20'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 20, 10),
	'diagwin50'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 50, 10),
	'diagwin100'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 100, 10),
    );
    
    return $autopicks_efficiency_report_numbers;
}

function get_lotto_patterns_autopicks_efficiency_report($lottery_name, $draw_num, $draw_num_val, $num_of_draws){
    $header = "<table><tbody>";
    
    $labels1 = "<tr>";
    $labels1 .="<th></th>";
    $labels1 .="<th colspan='2' >DrawDetails</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='2' >Autopicks</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin5</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin10</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin20</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin50</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin100</th>";
    $labels1 .="</tr>";
    
    $labels2 = "<tr>";
    $labels2 .="<th></th>";
    $labels2 .="<th>Draw#</th><th>DrawTime</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>Diagonal</th><th>Ladder</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="</tr>";
    
    $report = "";
    
    for($i=0; $i < $num_of_draws; $i++){
	$draw_num_i = $draw_num - $i;
	$draw_num_val_i = $draw_num_val - $i;
	$report_data = lotto_patterns_autopicks_efficiency_report_data($lottery_name, $draw_num_i, $draw_num_val_i);
    
	
	$report .= "<tr>";
	$report .="<th>".$i."</th>";

	$report .="<td>".$report_data['draw_details']['draw_num']."</td>";
	$report .="<td>".$report_data['draw_details']['draw_time']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['autopicks']['diagonal']['match']."</td>";
	$report .="<td>".$report_data['autopicks']['ladder']['match']."</td>";
	$report .="<th class='black' ></td>";


	$report .="<td>".$report_data['diagwin5']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin5']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin5']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin5']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin10']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin10']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin10']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin10']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin20']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin20']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin20']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin20']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin50']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin50']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin50']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin50']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";


	$report .="<td>".$report_data['diagwin100']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin100']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin100']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin100']['z2updown']['match']."</td>";

	$report .="</tr>";
	
    }
 
    $footer .= "</tbody></table>";
    
    $autopicks_efficiency_report = $header.$labels1.$labels2.$report.$footer;
    
    return $autopicks_efficiency_report;
}

function ajx_autopicks_efficiency_report($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $draw_num + 1;
    $num_of_draws = $form_state['values']['num_of_draws'];
    
    $autopicks_efficiency_report = get_lotto_patterns_autopicks_efficiency_report("lotto_keno", $draw_num, $draw_num_val, $num_of_draws);
    $form['efficiency']['efficiency_report']['report']['#markup']=$autopicks_efficiency_report;

    return $form['efficiency']['efficiency_report']['report'];
}
?>
