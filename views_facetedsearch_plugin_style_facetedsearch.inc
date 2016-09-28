<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class views_facetedsearch_plugin_style_facetedsearch extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  // Build the settings form for the view.
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $selectedFields = $form_state['view']->display_handler->display->handler->view->
        display['default']->handler->view->display_handler->default_display->display->
        display_options['fields'];

    $form['views_facetedsearch_table'] = array(
      '#markup' => '<table>',
    );

    foreach($selectedFields as $selectedFieldKey => $eachSelectedField){

      $form['views_facetedsearch_row_' . $selectedFieldKey] = array(
        '#markup' => '<tr><td>',
      );

      $facetOptionKey = 'views_facetedsearch_facets_' . $eachSelectedField['field'] ;
      if (array_key_exists('label', $eachSelectedField)){
        $optionTitle = t($eachSelectedField['label']);
      }
      else {
        $optionTitle = t($eachSelectedField['id']);
      }

      if (array_key_exists($facetOptionKey, $this->options)){
        $currentValue = $this->options[$facetOptionKey];
      }
      else {
        $currentValue = NULL;
      }

      $form[$facetOptionKey] = array(
        '#type' => 'checkbox',
        '#title' => t('Allow searching by ' . $optionTitle),
        '#default_value' => $currentValue,
        // '#description' => t('Check box to display allow searching by this facet.'),
      );

      $form['views_facetedsearch_cell_separator_' . $selectedFieldKey] = array(
        '#markup' => '</td><td>',
      );

      $orderOptionKey = 'views_facetedsearch_facetorders_' . $eachSelectedField['field'] ;

      if (array_key_exists($orderOptionKey, $this->options)){
        $currentValue = $this->options[$orderOptionKey];
      }
      else {
        $currentValue = NULL;
      }

      $form[$orderOptionKey] = array(
        '#type' => 'checkbox',
        '#title' => t('Allow ordering by ' . $optionTitle),
        '#default_value' => $currentValue,
        // '#description' => t('Check box to display allow ordering by this facet.'),
      );

      $form['views_facetedsearch_row_close_' . $selectedFieldKey] = array(
        '#markup' => '</td></tr>',
      );
    }

    $form['views_facetedsearch_table_close'] = array(
      '#markup' => '</table>',
    );

    $form['views_facetedsearch_enable_pagination'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable Pagination'),
        '#default_value' => $this->options['views_facetedsearch_enable_pagination'],
        '#description' => t('Check box to display allow searching by facet.'),
      );

    $form['views_facetedsearch_pagination_count'] = array(
      '#type' => 'textfield',
      '#title' => t('Pagination Count'),
      '#default_value' => $this->options['views_facetedsearch_pagination_count'],
      '#description' => t('Check box to display allow searching by facet.'),
    );

  /*  $form['views_facetedsearch_item_template'] = array(
      '#type' => 'textarea',
      '#title' => t('Item Template'),
      //'#default_value' => $this->options['views_facetedsearch_item_template'],
      //'#description' => t('Check box to display allow searching by facet.'),
    );*/
  }

  function render(){
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/underscore-1.1.7.js');
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/facetedsearch.js');

//    die(print_r(debug_print_backtrace(), TRUE));
    //print '<pre>' . print_r(debug_backtrace(), TRUE) . '</pre>';
    parent::render();

    //die(print_r($this->render_fields($this->view->result), TRUE));

    return theme($this->theme_functions(), array(
      'view' => $this->view,
      'options' => $this->options,
'rows' => $this->render_fields($this->view->result)
//'rows' => $this->view->result,
  //    'mapping' => $this->define_mapping(),
    ));
}


  /*function render_fields($result) {
    // die(print_r($result, TRUE));
  }*/
}