<?php

function get_lotto_keno_results_pattern_form($form, &$form_state){
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    drupal_add_js(drupal_get_path('module', 'lotto_core') . '/js/pattern_grid.js' );
    
    $form=array(   );
    $form['pattern_refresh']=array(
	'#type'=>'button',
	'#value'=>'Refresh Results',
	'#ajax'=>array(
	    'callback' => 'ajx_keno_results_pattern_refresh',
	    'wrapper'=>'ajx_keno_results_pattern_wrapper',
	    'method'=>'replace'
	),
	'#prefix'=>'<div class="container-inline">',
    );
    
    $form['auto_bets']=array(
	'#type'=>'button',
	 '#value'=>'Autopick',	 
	 '#ajax'=>array(
	    'callback' => 'ajx_autopick_bets',
	    'wrapper'=>'ajx_keno_bets_wrapper',
	    'method'=>'replace'
	),
    );
    
     $form['place_bets']=array(
	'#type'=>'button',
	 '#value'=>'Place Bets',
	 '#ajax'=>array(
	    'callback' => 'ajx_place_bets',
	    'wrapper'=>'ajx_keno_bets_wrapper',
	    'method'=>'replace'
	)	
    );
     
     $form['clear_bets']=array(
	'#type'=>'button',
	 '#value'=>'Clear Bets',
	 /*
	 '#ajax'=>array(
	    'callback' => 'ajx_clear_bets',
	    'wrapper'=>'ajx_keno_bets_wrapper',
	    'method'=>'replace'
	), */
    );
     
     $form['live_bets']=array(
	'#type'=>'checkbox',
	 '#title'=>t('Live'),
	 '#value'=>1,
	 '#suffix'=>'&nbsp &nbsp'
    );
     
     $form['bets_combined']=array(
	'#type'=>'checkbox',
	'#title'=>t('Combined'),
	 '#value'=>0,	 	 
	'#suffix'=>'</div>'
    );
     
     
    $form['bets'] = array(
	'#type'=>'fieldset',
	'#title'=>'Bets Form',
	'#collapsible' => TRUE,
	'#collapsed' => FALSE,
	'#prefix'=>'<div id="ajx_keno_bets_wrapper" >',
	'#suffix'=>'</div>'
    );
    $form['bets']['pattern_type']=array(
	'#type'=>'radios',
	'#title'=>t('Pattern Type: '),
	'#options'=>array(
	    1=>'Diagonal',
	    2=>'Pillar',
	    3=>'Ladder',
	    4=>'Sequence',
	    5=>'Previous Trend'
	),
	'#default_value'=>1,
	'#prefix'=>'<div class="container-inline">',
	'#suffix'=>'</div>'
    );
   
     $form['bets']['bets_for'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Bets For ID:'),	 
	    '#default_value'=>'',
	    '#size' => 20,
	    '#prefix'=>'<div class="container-inline" >'
	 );
     $form['bets']['bets_1'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Diagonal:'),	 
	    '#default_value'=>'',
	    '#size' => 30
	 );
     
     $form['bets']['bets_2'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Pillar:'),	 
	    '#default_value'=>'',
	    '#size' => 30,	 	 
	    '#suffix'=>'</div>'
	 );
      $form['bets']['bets_3'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Ladder:'),	  
	    '#default_value'=>'',
	    '#size' => 30,
	    '#prefix'=>'<div class="container-inline">'
	 );
       $form['bets']['bets_4'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Sequence:'),	   
	    '#default_value'=>'',
	    '#size' => 30,
	 );
        $form['bets']['bets_5'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Previous Trend:'),
	    '#default_value'=>'',
	    '#size' => 30,
	    '#suffix'=>'</div><BR>'
	 );

   
    $form['bets']['pattern_grid'] = array(
	'#markup'=> lotto_pattern_grid_create("lotto_keno"),
	'#prefix'=>'<div id="ajx_keno_results_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    return $form;
}

function ajx_keno_results_pattern_refresh($form, $form_state){
    lotto_results_n_stats_sync_by_draw_numbers("lotto_keno");
    
    $form['bets']['pattern_grid']['#markup'] = lotto_pattern_grid_create("lotto_keno");
    
    return $form['bets']['pattern_grid'];
}

function ajx_place_bets($form, &$form_state){
    $i=1; $x=5;
    while ($i <= $x){
	$bets_data = array();
	$bets_data['lkbid'] = null;
	$bets_data['uid'] = 1;
	$bets_data['draw_number'] = $form_state['values']['bets_for'] + 1;
	$bets_data['live_bets_flag'] = $form_state['values']['live_bets'];
	$bets = trim($form_state['values']["bets_".$i]);
	$bets_collection = array();
	if ( strlen($bets) > 0){
	    $bet_array = explode(" ", $bets);
	    $bets_data['pattern_type'] = $i;
	    $count =0; $count_limit = 10; $extra_limit_bets = array();
	    foreach( $bet_array as $ind=>$bet){
		if ( strlen($bet) > 0) {
		    $count++;
		   if( $count <= $count_limit ){
		       $index = $ind + 1;
			$bets_data['b'.$index]  = trim($bet) ;
			$bets_data['picks'] = $count;
		   } else {
		       array_push($extra_limit_bets, trim($bet));
		   }	
		}
	    }
	    
	    if ( $form_state['values']['bets_combined'] == 1 ){
		array_push($bets_collection, $bets_data);
		if ($i == 5){
		    
		}
	    } else {
		$inserted = db_insert('lotto_keno_bets')->fields($bets_data)->execute();
	    }
	}
	$i++;
    }
    
    $form['bets'] = ajx_clear_bets($form, $form_state);
    
    return $form['bets'];
}

function ajx_clear_bets($form, $form_state){
    $form['bets']['#prefix']='<div id="ajx_keno_bets_wrapper" >';
    $form['bets']['#suffix']='</div>';
    
    $form['bets']['bets_for']['#default_value']="";
    $form['bets']['bets_1']['#value']="";
    $form['bets']['bets_2']['#value']="";
    $form['bets']['bets_3']['#value']="";
    $form['bets']['bets_4']['#value']="";
    $form['bets']['bets_5']['#value']="";
    
    return $form['bets'];
}

function ajx_autopick_bets($form, $form_state){
    $lotto_draw_num = $form_state['values']['bets_for'];
    $auto_picks =  lotto_bets_autopick('lotto_keno', $lotto_draw_num);
    
    $form['bets']['bets_1']['#value']= autopicks_to_string($auto_picks['diagonal']);
    $form['bets']['bets_2']['#value']= autopicks_to_string($auto_picks['pillar']);
    $form['bets']['bets_3']['#value']= autopicks_to_string($auto_picks['ladder']);
    $form['bets']['bets_4']['#value']= autopicks_to_string($auto_picks['sequence']);
    $form['bets']['bets_5']['#value']= autopicks_to_string($auto_picks['previous_trend']);
    
    $form['bets']['pattern_grid']['#markup'] = lotto_pattern_grid_create("lotto_keno",1,100,array_merge($auto_picks['diagonal'], $auto_picks['pillar'], $auto_picks['ladder'], $auto_picks['sequence'], $auto_picks['previous_trend'] ));
    
     return $form['bets'];
}

function autopicks_to_string($autopicks_array){    
    $str='';
    foreach($autopicks_array as $pick){
	$str .= $pick.' ';
    }
    $str = substr($str, 0, -1);
    return $str;    
}
?>
