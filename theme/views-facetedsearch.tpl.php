<table id='view_facetedsearch_facets'><tr></tr></table>
<div class=facettotalcount></div>
<div class=deselectstartover>Deselect all filters</div>
<?php print $views_facetedsearch_resultscontainer; ?>
<script type="text/javascript">
  jQuery(function(){
    var item_template = '<?php print $views_facetedsearch_itemtemplate; ?>';
    settings = {
      items              : views_facetedsearch_resultitems,
      facets             : { <?php print $views_facetedsearch_facets; ?> },
      resultSelector     : '#view_facetedsearch_results',
      facetSelector      : '#view_facetedsearch_facets',
      facetContainer     : '<?php print $views_facetedsearch_facetcontainer ?>',
      facetListContainer : '<?php print $views_facetedsearch_facetlistcontainer ?>',
      resultTemplate     : item_template,
      enablePagination   : <?php print $view->style_options['views_facetedsearch_enable_pagination'] ? 'true' : 'false' ?>,
      paginationCount    : <?php print $view->style_options['views_facetedsearch_pagination_count']  ? 
                                       $view->style_options['views_facetedsearch_pagination_count'] : '0' ?>,
      bottomContainer    : '<table><tr class=bottomline></tr></table>',
      orderByTemplate    : '<td class=orderby><span class="orderby-title">Sort by: </span><ul><% _.each(options, function(value, key) { %>'+
                           '<li class=orderbyitem id=orderby_<%= key %>>'+
                           '<%= value %> </li> <% }); %></ul></td>',
      countTemplate      : '<td class=facettotalcount><%= count %> Results</td>',
      deselectTemplate   : '<td class=deselectstartover>Deselect all filters</td>',
      orderByOptions     : { <?php print $views_facetedsearch_facetorders ?> }
    }

    // use them!
    jQuery.facetelize(settings);
  });

  var views_facetedsearch_resultitems = [
  <?php
    // Populate the results items from the views data.
    $resultCount = count($view->result);
    $resultIndex = 0;

    if (count($view->style_plugin->rendered_fields) > 0){
      $attributeCount = count((array) $view->style_plugin->rendered_fields[0]);
    }

    foreach ($view->style_plugin->rendered_fields  as $resultIndex => $eachResult) {
      $eachResult = (array) $eachResult; // Cast each object into an array.
      $attributeIndex = 0;
      print '{';
      foreach ($eachResult as $attributeKey => $attribute){
        print '"' . addslashes($attributeKey) . '" : "' . addslashes(str_replace(array("\r", "\n"), '', $attribute)) . '"';
        $attributeIndex++;
        if ($attributeIndex != $attributeCount){
          print ',';
        }
        print "\n";
      }
      print '}';
      $resultIndex ++;
      if ($resultIndex != $resultCount){
        print ",\n";
      }
    }
  ?>
];
</script>