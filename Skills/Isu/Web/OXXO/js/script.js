$('.item').hover(
	function() {
		$(this).children('.desc').animate({ 'bottom': '0' });
	}, function() {
		$(this).children('.desc').animate({ 'bottom': '-80px' });
	}
);