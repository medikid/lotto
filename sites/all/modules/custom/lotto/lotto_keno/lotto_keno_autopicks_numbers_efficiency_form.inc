<?php

function get_lotto_keno_autopicks_numbers_efficiency_form($form, &$form_state){
    
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    if (isset($draw_num)){
	$last_keno_draw_num = $draw_num;
    } else $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno") - 1;
    $last_keno_draw_num_val = $last_keno_draw_num + 1;
    $top_of = 10;
    
    $numbers_spiral =  get_autopicks_efficiency_report_numbers_spiral("lotto_keno", $last_keno_draw_num, $last_keno_draw_num_val, $top_of);
       
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
	    'callback' => 'ajx_numbers_draw_number_prev',
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
	    'callback' => 'ajx_numbers_draw_number_next',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    );
    $form['efficiency']['autopicks_profile'] = array(
	'#type'=>'select',
	'#title'=>'Profile:',
	'#options'=>array(
	    0=>'Select Profile',
	    1=>'DiagWinNormal',
	    2=>'DiagWinNormal-t',
	    3=>'DiagWinSpiral',
	    4=>'DiagWinSpiral-t'
	),
	'#default_value'=>4
    );
    
    
    $form['efficiency']['refresh']=array(
	'#type'=>'button',
	'#value'=>t('Refresh'),
	'#ajax'=>array(
	    'callback' => 'ajx_autopicks_efficiency_refresh',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    );
     
    $form['efficiency']['top_of']=array(
	'#type'=>  'textfield',
	'#title'=>t("No of Picks#: "),
	'#default_value'=>15,
	'#size'=> 11	
    );
    
    $form['efficiency']['draw_number_val']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw Result#: "),
	'#default_value'=>$last_keno_draw_num_val,
	'#size'=> 11	
    );
    
    
    $form['efficiency']['numbers']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['numbers']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral("lotto_keno", $numbers_spiral)
	
    );
    
     $form['efficiency']['numbers_pattern']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Pattern:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['numbers_pattern']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral("lotto_keno", $numbers_spiral),
	
    );
    
    $form['efficiency']['numbers_score']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Score:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['numbers_score']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral)	
    );
    return $form;
}

function ajx_numbers_draw_number_prev($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $form_state['values']['draw_number_val'];
    $draw_num_prev = $draw_num-1;
    $draw_num_prev_val = $draw_num_val - 1;
    $top_of = $form_state['values']['top_of'];
    
    $numbers_spiral = get_autopicks_efficiency_report_numbers_spiral("lotto_keno", $draw_num_prev, $draw_num_prev_val, $top_of);
    $numbers_grid = lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_pattern_grid = lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_score_grid = lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_prev;
    $form['efficiency']['draw_number_val']['#value'] = $draw_num_prev_val;
    $form['efficiency']['numbers']['grid']['#markup'] = $numbers_grid;
    $form['efficiency']['numbers_pattern']['grid']['#markup'] = $numbers_pattern_grid;
    $form['efficiency']['numbers_score']['grid']['#markup'] = $numbers_score_grid;
    
	
    return $form['efficiency'];
}

function ajx_numbers_draw_number_next($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $form_state['values']['draw_number_val'];
    $draw_num_next = $draw_num + 1;
    $draw_num_next_val = $draw_num_val + 1;
    $top_of = $form_state['values']['top_of'];
    
    $numbers_spiral = get_autopicks_efficiency_report_numbers_spiral("lotto_keno", $draw_num_next, $draw_num_next_val, $top_of);
    $numbers_grid = lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_pattern_grid = lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_score_grid = lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_next;
    $form['efficiency']['draw_number_val']['#value'] = $draw_num_next_val;
    $form['efficiency']['numbers']['grid']['#markup'] = $numbers_grid;
    $form['efficiency']['numbers_pattern']['grid']['#markup']= $numbers_pattern_grid;
    $form['efficiency']['numbers_score']['grid']['#markup'] = $numbers_score_grid; 
    
    return $form['efficiency'];
}


function lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral($lottery_name, $autopicks_apd_numbers_spiral){
     $autopicks_numbers_pattern_grid = "";
     
	switch($lottery_name){
	    case 'lotto_max':
		break;
	    case 'lotto_keno':
		$x=1; $y=80; $scores=array();
		$report_data_spiral = $autopicks_apd_numbers_spiral;
		
		$lotto_results = $report_data_spiral['lotto_results'];
		$autopicks = $report_data_spiral['autopick_nbrs'];
		$diagwin5 = $report_data_spiral['diagwin5'];
		$diagwin10 = $report_data_spiral['diagwin10'];
		$diagwin20 = $report_data_spiral['diagwin20'];
		$diagwin50 = $report_data_spiral['diagwin50'];
		$diagwin100 = $report_data_spiral['diagwin100'];
		
		
		
		
		$header = "<table><tbody>";
		$labels = "<tr><th></th>";
		for($i=1; $i <= 80; $i++){
		    $labels .= "<th";
		    $labels .= ( in_array($i, $lotto_results)) ? " class=\"selected\" >" : " >";
		    $labels .= $i;
		    $labels .= "</th>";
		    
		    $scores[$i] = 0;
		}
		$labels .= "</tr>";

		$report ="";
		
		$report .= "<tr>";
		$report .= "<th>AutoPick-Diag</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $autopicks['diagonal']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"black\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>AutoPick-Ladder</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $autopicks['ladder']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"black\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";

		$report .= "<tr>";
		$report .= "<th>Pillar-5</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin5['pillar']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"blue\" >";
		    $report .="</td>";
		}		
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Pillar-10</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin10['pillar']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x : " class=\"blue\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Pillar-20</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin20['pillar']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"blue\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Pillar-50</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin50['pillar']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"blue\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Pillar-100</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin100['pillar']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"blue\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepup-5</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin5['stepup']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"brown\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepup-10</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin10['stepup']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"brown\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepup-10</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin10['stepup']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"brown\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepup-20</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin20['stepup']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"brown\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepup-50</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin50['stepup']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"brown\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepup-100</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin100['stepup']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"brown\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepdown-5</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin5['stepdown']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"grey\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepdown-10</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin10['stepdown']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"grey\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepdown-20</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin20['stepdown']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"grey\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepdown-50</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin50['stepdown']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"grey\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Stepdown-100</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td";
		    $report .=( in_array($x, $diagwin100['stepdown']) ) ? ( in_array($x, $lotto_results)) ? " class=\"green\" >".$x : " >".$x  : " class=\"grey\" >";
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		$report .= "<tr>";
		$report .= "<th>Score-Ovrl</th>";
		for($x=1; $x <= $y; $x++){
		    $report .="<td>";
		    $report .=$scores[$x];
		    $report .="</td>";
		}
		$report .= "</tr>";
		
		
		
		$footer .= "</tbody></table>";

		$autopicks_numbers_pattern_grid = $header.$labels.$report.$footer;


			break;
	}
     return $autopicks_numbers_pattern_grid;
}


function lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral($lottery_name, $autopicks_apd_numbers_spiral){
     $autopicks_numbers_grid = "";
     
	switch($lottery_name){
	    case 'lotto_max':
		break;
	    case 'lotto_keno':
		$report_data_spiral =   $autopicks_apd_numbers_spiral;
		$top_of = 10;
		
		
		$header = "<table><tbody>";

		$labels1 = "<tr>";
		$labels1 .="<th></th>";
		$labels1 .="<th colspan='2' >Autopicks</th>";
		$labels1 .="<th class='black' ></th>";
		$labels1 .="<th colspan='5' >DiagWin5</th>";
		$labels1 .="<th class='black' ></th>";
		$labels1 .="<th colspan='5' >DiagWin10</th>";
		$labels1 .="<th class='black' ></th>";
		$labels1 .="<th colspan='5' >DiagWin20</th>";
		$labels1 .="<th class='black' ></th>";
		$labels1 .="<th colspan='5' >DiagWin50</th>";
		$labels1 .="<th class='black' ></th>";
		$labels1 .="<th colspan='5' >DiagWin100</th>";
		$labels1 .="</tr>";

		$labels2 = "<tr>";
		$labels2 .="<th></th>";
		$labels2 .="<th>Diagonal</th><th>Ladder</th>";
		$labels2 .="<th class='black' ></th>";
		$labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
		$labels2 .="<th class='black' ></th>";
		$labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
		$labels2 .="<th class='black' ></th>";
		$labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
		$labels2 .="<th class='black' ></th>";
		$labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
		$labels2 .="<th class='black' ></th>";
		$labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
		$labels2 .="</tr>";

		$report = "";

		for($i=1; $i <= $top_of; $i++){
		    
		    $report .= "<tr>";
		    $report .="<th>".$i."</th>";
		    $index = $i-1;

		    $report .="<td";
		    $report .=(in_array($report_data_spiral['autopick_nbrs']['diagonal'][$index], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['autopick_nbrs']['diagonal'][$index]."</td>";
		    $report .="<td";
		    $report .=(in_array($report_data_spiral['autopick_nbrs']['ladder'][$index], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['autopick_nbrs']['ladder'][$index]."</td>";
		    $report .="<th class='black' ></th>";

		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin5']['pillar'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin5']['pillar'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin5']['stepup'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin5']['stepup'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin5']['stepdown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin5']['stepdown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin5']['z1updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin5']['z1updown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin5']['z2updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin5']['z2updown'][$i] ."</td>";
		    $report .="<th class='black' ></th>";

		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin10']['pillar'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin10']['pillar'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin10']['stepup'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin10']['stepup'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin10']['stepdown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin10']['stepdown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin10']['z1updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin10']['z1updown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin10']['z2updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin10']['z2updown'][$i] ."</td>";
		    $report .="<th class='black' ></th>";

		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin20']['pillar'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin20']['pillar'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin20']['stepup'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin20']['stepup'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin20']['stepdown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin20']['stepdown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin20']['z1updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin20']['z1updown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin20']['z2updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin20']['z2updown'][$i] ."</td>";
		    $report .="<th class='black' ></th>";

		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin50']['pillar'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin50']['pillar'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin50']['stepup'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin50']['stepup'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin50']['stepdown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin50']['stepdown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin50']['z1updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin50']['z1updown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin50']['z2updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin50']['z2updown'][$i] ."</td>";
		    $report .="<th class='black' ></th>";

		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin100']['pillar'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin100']['pillar'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin100']['stepup'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin100']['stepup'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin100']['stepdown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin100']['stepdown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin100']['z1updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin100']['z1updown'][$i] ."</td>";
		    $report .="<td";
		    $report .= (in_array($report_data_spiral['diagwin100']['z2updown'][$i], $report_data_spiral['lotto_results'])) ? " class=\"green\" >" : ">";
		    $report .= $report_data_spiral['diagwin100']['z2updown'][$i] ."</td>";
		    
		    $report .="</tr>";

		}

		$footer .= "</tbody></table>";

		$autopicks_numbers_grid = $header.$labels1.$labels2.$report.$footer;


			break;
	}
     return $autopicks_numbers_grid;
}

function lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral($lottery_name, $autopicks_apd_numbers_spiral){
    $score_grid = "";
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $x=1; $y=80; $scores=array();
	    for($x=1; $x <= $y; $x++){
		$scores[$x]['diagonal'] = 0;
		$scores[$x]['ladder'] = 0;
		$scores[$x]['pillar'] = 0;
		$scores[$x]['stepup'] = 0;
		$scores[$x]['stepdown'] = 0;
	    }
		$report_data_spiral = $autopicks_apd_numbers_spiral;
		
		$lotto_results = $report_data_spiral['lotto_results'];
		$autopicks = $report_data_spiral['autopick_nbrs'];
		$diagwin5 = $report_data_spiral['diagwin5'];
		$diagwin10 = $report_data_spiral['diagwin10'];
		$diagwin20 = $report_data_spiral['diagwin20'];
		$diagwin50 = $report_data_spiral['diagwin50'];
		$diagwin100 = $report_data_spiral['diagwin100'];
		
		
	    $score_autopick = 100;
		$score_5 = 5;
		$score_10 = 10;
		$score_20 = 20;
		$score_50 = 50;
		$score_100 = 100;
		
		
		/*********************************************************/
		foreach($autopicks['diagonal'] as $rank=>$num){
		    $scores[$num]['diagonal'] += $score_autopick;
		}
		foreach($autopicks['ladder'] as $rank=>$num){
		    $scores[$num]['ladder'] += $score_autopick;
		}
		foreach($diagwin5 as $cat=>$data){
		   foreach($data as $rank=>$num){
		        $scores[$num][$cat] += $score_5;
		    }		    
		    		    
		}
		foreach($diagwin10 as $cat=>$data){
		    foreach($data as $rank=>$num){
			$scores[$num][$cat] += $score_20;
		    }		    
		}
		foreach($diagwin20 as $cat=>$data){
		    foreach($data as $rank=>$num){
			$scores[$num][$cat] += $score_20;
		    }		    
		}
		foreach($diagwin50 as $cat=>$data){
		    foreach($data as $rank=>$num){
			$scores[$num][$cat] += $score_50;
		    }		    
		}
		foreach($diagwin100 as $cat=>$data){
		    foreach($data as $rank=>$num){
			$scores[$num][$cat] += $score_100;
		    }		    
		}
		    $autopicks = array();
		    $overall = array();
		    $stepup = array();
		    $pillar = array();
		    $stepdown =  array();
		
		   foreach($scores as $num=>$data){
		       $autopicks[$num]= $data['diagonal'] + $data['ladder'];
		       $pillar[$num] = $data['pillar'];
			$stepup[$num] = $data['stepup'];
			$stepdown[$num] = $data['stepdown'];
			$overall[$num] = $autopicks[$num] + $pillar[$num] + $stepup[$num] + $stepdown[$num];
		    }
		
		arsort($autopicks);
		arsort($pillar);
		arsort($stepup);
		arsort($stepdown);
		arsort($overall);
		
		$scores = array();
		$rank=1;
		foreach($autopicks as $num=>$score){
		    $scores[$rank]['autopicks'] = array( 'num'=>$num, 'score'=>$score );
		    $rank++;
		}
		$rank=1;
		foreach($pillar as $num=>$score){
		    $scores[$rank]['pillar'] = array( 'num'=>$num, 'score'=>$score );
		    $rank++;
		}
		$rank=1;
		foreach($stepup as $num=>$score){
		    $scores[$rank]['stepup'] = array( 'num'=>$num, 'score'=>$score );
		    $rank++;
		}
		$rank=1;
		foreach($stepdown as $num=>$score){
		    $scores[$rank]['stepdown'] = array( 'num'=>$num, 'score'=>$score );
		    $rank++;
		}
		$rank=1;
		foreach($overall as $num=>$score){
		    $scores[$rank]['overall'] = array( 'num'=>$num, 'score'=>$score );
		    $rank++;
		}
		
		/*********************************************************/
	    
	    $header = "<table><tbody>";
	    $labels = "<tr>";
	    $labels .= "<th>Rank</th>";
	    $labels .=  "<th>Overall</th>";
	    $labels .=  "<th>Pillar</th>";
	    $labels .=  "<th>Stepup</th>";
	    $labels .= "<th>Stepdown</th>";;
	    $labels .= "</tr>";
	    
	    $body = "";
	    foreach($scores as $rank=>$data){		
		$body .="</tr>";
		$body .= "<th>".$rank."</th>";
		$body .= "<td";
		$body .= ( in_array($data['overall']['num'], $lotto_results)) ? " class=\"green\" >" : (($rank <= 10 ) ? " class=\"yellow\" >": ">");
		$body .=$data['overall']['num']."(".$data['overall']['score'].")";
		$body .="</td>";
		$body .= "<td";
		$body .= ( in_array($data['pillar']['num'], $lotto_results)) ? " class=\"green\" >" : (($rank <= 10 ) ? " class=\"yellow\" >": ">");
		$body .=$data['pillar']['num']."(".$data['pillar']['score'].")";
		$body .="</td>";
		$body .= "<td";
		$body .= ( in_array($data['stepup']['num'], $lotto_results)) ? " class=\"green\" >" : (($rank <= 10 ) ? " class=\"yellow\" >": ">");
		$body .=$data['stepup']['num']."(".$data['stepup']['score'].")";
		$body .="</td>";
		$body .= "<td";
		$body .= ( in_array($data['stepdown']['num'], $lotto_results)) ? " class=\"green\" >" : (($rank <= 10 ) ? " class=\"yellow\" >": ">");
		$body .=$data['stepdown']['num']."(".$data['stepdown']['score'].")";
		$body .="</td>";
		$body .="</tr>";		
	    }
	    
	    
	    $footer .= "</tbody></table>";
	    $score_grid = $header . $labels . $body . $footer;
	    break;
    }
    return $score_grid;
}
?>
