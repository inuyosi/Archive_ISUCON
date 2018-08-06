$(document).ready(function(){
 var search = function(check){
  $.ajax({
    type: 'GET',
    url: 'http://13.114.125.39:3000/addresses.json',
    data: check,
    dataType: 'json',
    success: function(response){
      page_number(response["total"],response["per"],response["page"]);
      var data = $("#data");
      data.empty();
    $.each(response["results"], function(index){
        var row = $("<tr></tr>");
        row.append($("<td>" + this.id + "</td>")).
          append($("<td>" + this.name + "</td>")).
          append($("<td>" + this.name_kana + "</td>")).
          append($("<td>" + this.gender + "</td>")).
          append($("<td>" + this.phone + "</td>")).
          append($("<td>" + this.mail + "</td>")).
          append($("<td>" + this.zipcode + "</td>")).
          append($("<td>" + this.address1 + "</td>")).
          append($("<td>" + this.address2 + "</td>")).
          append($("<td>" + this.address3 + "</td>")).
          append($("<td>" + this.address4 + "</td>")).
          append($("<td>" + this.address5 + "</td>")).
          append($("<td>" + this.age + "</td>"));
        data.append(row);
      });
    }
  });
 }

 var check = function(check){
     if(check == undefined){
      check = {};
    }
    $.each($(".search"), function(index){
      if(this.value != ""){
        check[this.name] = this.value;
      }
    });
    return check;
  }

  var page_number = function(total, per, page){
  var offset = 5;
  var pagination = $("nav ul.pagination");
  var totalPage = Math.ceil(total / per);
  var startPage, endPage;

    if(page + offset < totalPage && page - offset > 0) {
      startPage = page - offset;
      endPage = page + offset;
    } else if(page - offset < 1){
      startPage = 1;
      endPage = (startPage + offset * 2) < totalPage ? startPage + offset * 2 : totalPage;
    } else {
      startPage = (totalPage - offset * 2 < 1) ? 1 : totalPage - offset * 2;
      endPage = totalPage;
    }

   pagination.empty();

for(var i = startPage; i <= endPage; i++){
      if(i == page){
        pagination.append($('<li class="active move-page"><a href="#">' + i + '</a></li>'));
      } else {
        pagination.append($('<li class="move-page"><a href="#">' + i + '</a></li>'));
      }

    }
    if(page == 1) {
      pagination.prepend($('<li class="move-prev disabled"><a href="#" aria-label="Previous"><span aria-hidden="true">&laquo;</span></a></li>'));
    } else {
      pagination.prepend($('<li class="move-prev"><a href="#" aria-label="Previous"><span aria-hidden="true">&laquo;</span></a></li>'));
    }

    if(page == totalPage) {
      pagination.append($('<li class="move-next disabled"><a href="#" aria-label="Next"><span aria-hidden="true">&raquo;</span></a></li>'));
    } else {
      pagination.append($('<li class="move-next"><a href="#" aria-label="Next"><span aria-hidden="true">&raquo;</span></a></li>'));
    }

   // pagination event
    pagination.find("li.move-page a").on("click", function(e){
      search(check({ page: $(this).text() }));
    });

    pagination.find("li.move-next a").on("click", function(e){
      if(page < totalPage){
        search(check({ page: page + 1 }));
      }
    });

    pagination.find("li.move-prev a").on("click", function(e){
      if(page > 1){
        search(check({ page: page - 1 }));
      }
    })

 }

    search(check());

  $(".search").on("change", function(e){
    search(check());
  });

  $(".search#per-page").on("change", function(e){
    search(check());
  });
});
