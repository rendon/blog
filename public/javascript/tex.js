$(function() {
    // Set numbers to references.
    var figureNumbers = {};
    var figNum = 1;
    $('figure[id^=label_]').get().forEach(function(fig) {
        var id = fig.getAttribute('id').replace(/^label_/, '');
        if (figureNumbers[id] === undefined) {
            figureNumbers[id] = figNum++;
        }
    });

    $('span[name^=ref_]').get().forEach(function(ref) {
        var id = ref.getAttribute('name').replace(/^ref_/, '');
        if (figureNumbers[id] !== undefined) {
            $(ref).html(figureNumbers[id]);
        }
    });

    // Set numbers to cites.
    var citeNumbers = {};
    var citeNum = 1;
    $('a[id^=label_]').get().forEach(function(bib) {
        var id = bib.getAttribute('id').replace(/^label_/, '');
        if (citeNumbers[id] === undefined) {
            citeNumbers[id] = citeNum++;
        }
    });

    $('span[name^=cite_]').get().forEach(function(cite) {
        var id = cite.getAttribute('name').replace(/^cite_/, '');
        $(cite).html(citeNumbers[id]);
    });
});
