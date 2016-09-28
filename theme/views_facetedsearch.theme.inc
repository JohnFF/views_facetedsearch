<?php

function  _views_facetedsearch_preprocess_views_facetedsearch(&$vars){
  $vars['views_facetedsearch_facets'] = _views_facetedsearch_get_facets($vars['view'], 'views_facetedsearch_facets_');
  $vars['views_facetedsearch_facetorders'] = _views_facetedsearch_get_facets($vars['view'], 'views_facetedsearch_facetorders_');
}

function _views_facetedsearch_get_facets($view, $option_start){
  $optionsArray = array();
  foreach($view->display['default']->handler->options['fields'] as $key => $facet){
    if (!array_key_exists($option_start . $key, $view->style_options)){
      continue;
    }

    if ($view->style_options[$option_start . $key] === 0){
      continue;
    }

    if (array_key_exists('label', $view->display['default']->handler->options['fields'][$key])) {
      $label = $view->display['default']->handler->options['fields'][$key]['label'];
    }
    else {
      $label = $facet;
    }
    $optionsArray[] = "'$key' : '$label'";
  }
  $facetOptionsString = implode(', ', $optionsArray);
  return $facetOptionsString;
}