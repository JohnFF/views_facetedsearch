<?php print $views_facetedsearch_facetpanel ?>
<?php print $views_facetedsearch_controlpanel ?>
<?php print $views_facetedsearch_resultscontainer; ?>
<script type="text/javascript">
  jQuery(function(){
    var item_template = '<?php print $views_facetedsearch_itemtemplate; ?>';
    settings = {
      items              : views_facetedsearch_resultitems,
      facets             : { <?php print $views_facetedsearch_facets; ?> },
      resultSelector     : '#view_facetedsearch_results',
      facetSelector      : '#view_facetedsearch_facetpanel',
      facetContainer     : '<?php print $views_facetedsearch_facetcontainer ?>',
      facetListContainer : '<?php print $views_facetedsearch_facetlist ?>',
      resultTemplate     : item_template,
      enablePagination   : <?php print $view->style_options['views_facetedsearch_enable_pagination'] ? 'true' : 'false' ?>,
      paginationCount    : <?php print $view->style_options['views_facetedsearch_pagination_count']  ? 
                                       $view->style_options['views_facetedsearch_pagination_count'] : '0' ?>,
      resultsHeader      : '<?php print $view->style_options['views_facetedsearch_resultsheader'] ?>',
      bottomContainer    : '',
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
  <?php print $views_facetedsearch_results ?>
];
</script>