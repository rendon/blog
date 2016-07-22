$(function() {
    var figureNumbers = {}
    var number = 1;
    $('figure[id^=label_').get().forEach(function(fig) {
        var id = fig.getAttribute('id').replace(/^label_/, '');
        if (figureNumbers[id] === undefined) {
            figureNumbers[id] = number++;
        }
    });

    $('span[name^=ref_').get().forEach(function(ref) {
        var id = ref.getAttribute('name').replace(/^ref_/, '');
        if (figureNumbers[id] !== undefined) {
            $(ref).html(figureNumbers[id]);
        }
    });
});
