(function () {
    "use strict";

    var fileName;
    var fileOrigen;
    var fileDestino;
    var fileSymbols;

    WinJS.UI.Pages.define("/pages/home/home.html", {
        // This function is called whenever a user navigates to this page. It
        // populates the page elements with the app's data.
        ready: function (element, options) {
            // TODO: Initialize the page here.


            //document.getElementById('botonOrigen').addEventListener("click", openFilePickerOrigen, false);

            //document.getElementById('botonDestino').addEventListener("click", saveFilePickerDestino, false);

            //document.getElementById('botonSimbolos').addEventListener("click", saveFilePickerSimbolos, false);

            document.getElementById('compressButton').addEventListener("click", comprimir, false);

        }
    });

    function comprimir() {
        var codificacion = RuntimeComponent.ClaseCodificacion();
        var destino;
        Windows.Storage.KnownFolders.documentsLibrary.getFileAsync(document.getElementById("nombreArchivo").value).done(
            function (file) {
                // If file exists.
                document.getElementById('resultado').textContent = "leida"; //file.name
                Windows.Storage.FileIO.readBufferAsync(file).then(function (buffer) {
                    //var dataReader = Windows.Storage.Streams.DataReader.fromBuffer(buffer);
                    //var output = dataReader.readString(buffer.length);
                    var array = Uint8Array(buffer);
                    var simbolos = new Uint8Array();
                    destino = new Uint8Array(array.length);
                    var resultado = codificacion.codificar(array, simbolos, destino);
                    document.getElementById('resultado').textContent = resultado;

                    Windows.Storage.KnownFolders.documentsLibrary.createFileAsync(document.getElementById("nombreArchivo").value + ".hcf",
                        Windows.Storage.CreationCollisionOption.replaceExisting).then(function (archivoDestino) {
                            Windows.Storage.FileIO.writeBytesAsync(archivoDestino, destino).then(function () {
                                // Add code to do something after the text is written to the file
                            });
                    });

                });
            },
            function (err) {
                // If file doesn't exist, indicate users to use scenario 1.
                document.getElementById('resultado').textContent = err;
            }
        );





    }

})();
