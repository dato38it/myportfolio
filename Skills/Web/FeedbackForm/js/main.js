$(function() {
    var header = $("#header"),
        introH = $("#intro").innerHeight(),
        scrollOffset = $(window).scrollTop();
    /* Menu nav toggle */
    $("#nav_toggle").on("click", function(event) {
        event.preventDefault();
        $(this).toggleClass("active");
        $("#nav").toggleClass("active");
        $("#nav--colorWeb").toggleClass("active");
        $("#nav--colorIt").toggleClass("active");
    });
    /* Fixed Header */
    checkScroll(scrollOffset);
    $(window).on("scroll", function() {
        scrollOffset = $(this).scrollTop();

        checkScroll(scrollOffset);
    });
    function checkScroll(scrollOffset) {
        if( scrollOffset >= introH ) {
            header.addClass("fixed");
        } else {
            header.removeClass("fixed");
        }
    }
    /* Smooth scroll */
    $("[data-scroll]").on("click", function(event) {
        event.preventDefault();
        var $this = $(this),
            blockId = $this.data('scroll'),
            blockOffset = $(blockId).offset().top;
        $("#nav a").removeClass("active");
        /*$("#nav--colorWeb a").removeClass("active");*/
        $this.addClass("active");
        $("html, body").animate({
            scrollTop:  blockOffset
        }, 500);
    });
    /* Collapse */
    $("[data-collapse]").on("click", function(event) {
        event.preventDefault();
        var $this = $(this),
            blockId = $this.data('collapse');
        $this.toggleClass("active");
    });
    /* Modal*/
    const modalCall = $("[data-modal]");
    const modalClose = $("[data-close]");
    modalCall.on("click", function(event) {
        event.preventDefault();
        let $this = $(this);
        let modalId = $this.data('modal');
        $(modalId).addClass('show');
        $("body").addClass('no-scroll');
        setTimeout(function() {
            $(modalId).find(".modal__dialog").css({
                transform: "scale(1)"
            });
        }, 200);
        worksSlider.slick('setPosition');
    });
    modalClose.on("click", function(event) {
        event.preventDefault();
        let $this = $(this);
        let modalParent = $this.parents('.modal');
        modalParent.find(".modal__dialog").css({
            transform: "scale(0)"
        });
        setTimeout(function() {
            modalParent.removeClass('show');
            $("body").removeClass('no-scroll');
        }, 200);
    });
    $(".modal").on("click", function(event) {
        let $this = $(this);
        $this.find(".modal__dialog").css({
            transform: "scale(0)"
        });
        setTimeout(function() {
            $this.removeClass('show');
            $("body").removeClass('no-scroll');
        }, 200);
    });
    $(".modal__dialog").on("click", function(event) {
        event.stopPropagation();
    });
});
/*Раскрывающийся текст*/
var ns6=document.getElementById&&!document.all?1:0
var head="display:''"
var folder=''
function workHidden(curobj){
    folder=ns6?curobj.nextSibling.nextSibling.style:document.all[curobj.sourceIndex+1].style
    if (folder.display=="none")
        folder.display=""
    else
        folder.display="none"
}

