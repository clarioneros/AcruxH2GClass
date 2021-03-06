!ABCIncludeFile(Family)

OMIT('***')
 * User: Carlos Pizzi
 * Date: 28/11/2018
 *
 * 
 *  Lo que mas abajo no se si es as� o al rev�s... probar !!!
*   Definir en el proyecto para DLL
 * _AH2GLinkMode_=>1
 * _AH2GDllMode_=>0
 *
 *
 * Definir para EXE
 * _AH2GLinkMode_=>0
 * _AH2GDllMode_=>1


 ***



AH2G             Class,Module('AcruxH2GClass.clw'),Link('AcruxH2GClass.clw',_AH2GLinkMode_), DLL(_AH2GDllMode_)




sURLPrinter String(300)
sXMLFiscal  String(10)
InDebug     Byte
GSA          &GSalida



Construct           Procedure()
Destruct            Procedure()
Init                Procedure()
Kill                Procedure()




!!!<summary>Este comando permite consultar informaci�n asociada al error reportado por la impresora fiscal al intentar</summary>
!!!<summary>ejecutar el �ltimo comando enviado.</summary>
ConsultarUltimoError Procedure(),Byte


!!!<summary>Este comando permite consultar el estado general de la impresora fiscal, e informaci�n asociada al �ltimo tipo de</summary>
!!!<summary>comprobante emitido/cancelado que se especifique.</summary>
!!!<param name="pCodigoComprobante"> El tipo de comprobante a especificar debe ser alguno de los c�digos identificatorios tabulados en la normativa
!!!fiscal vigente. (AH2G:TipoComprobante). Default: AH2G:TipoComprobante:NoDocumento</param>
!!!<returns>Devuelve un String en formato JSON. Devuelve el estado general de la impresora. Leer Manual de Comandos.</returns>
ConsultarEstado Procedure(String pCodigoComprobante),String

ConsultarEstadoII Procedure(String pCodigoComprobante, *AH2G:GSalida pGSalida)


!!!<summary>Este comando permite abrir cualquier comprobante disponible para su emisi�n en la impresora fiscal.</summary> 
!!!<summary>Tenerpresente que para la apertura del comprobante en algunos casos se requiere de uno o m�s comandos previos en</summary>
!!!<summary>forma obligatoria, como por ejemplo: CargarDatosCliente, CargarDocumentoAsociado, y/u otros.</summary>
!!!<summary>En el caso de emisi�n del Documento Donaci�n se requiere adem�s, antes de la apertura del comprobante, del</summary>
!!!<summary>env�o del comando CargarBeneficiario.</summary>
!!!<summary>En el caso de emisi�n de un Remito ('R' o 'X') se requiere adem�s, antes de la apertura del comprobante, del env�o</summary>
!!!<summary>del comando CargarTransportista.</summary>
!!!<summary>El comando AbrirDocumento es el que imprime el encabezado del mismo.</summary>
!!!<param name="pCodigoComprobante" El tipo de comprobante a especificar debe ser alguno de los c�digos identificatorios tabulados en la normativa fiscal vigente. (AH2G:TipoComprobante)</param>
!!!<param name="pRazonSocial" Raz�n Social del cliente.</param>
!!!<param name="pNumeroDocumento" N�mero del Documento del cliente.</param>
!!!<param name="pResponsabilidadIVA" Responsabilidad IVA del cliente. (AH2G:ResponsabilidadIVA)</param>
!!!<param name="pTipoDocumentoCliente" Tipo de Documento del cliente. (AH2G:TipoDocumentoCliente)</param>
!!!<param name="pDomicilio" Domicilio del cliente.</param>
!!!<returns>N�mero De Comprobante | Cero o False=Error</returns>
AbrirDocumento  Procedure(String pCodigoComprobante, String pRazonSocial, String pNumeroDocumento, String pResponsabilidadIVA, | 
                          String pTipoDocumentoCliente, String pDomicilio),Long

CargarDatosCliente Procedure(String pRazonSocial, String pNumeroDocumento, String pResponsabilidadIVA, String pTipoDocumentoCliente, String pDomicilio),Byte,PRIVATE


!!!<summary>Este comando permite almacenar, en la memoria de trabajo de la impresora fiscal, informaci�n identificatoria de</summary>
!!!<summary>un comprobante determinado. Dicha informaci�n vincula al comprobante pr�ximo a emitir y al referenciado (o asociado).</summary>
!!!<param name="pNumeroLinea" Entre 0 y 2.</param>
!!!<param name="pCodigoComprobante" (TiposComprobante).</param>
!!!<param name="pNumeroPos" Entre 0 y 99999.</param>
!!!<param name="pNumeroComprobant" Entre 0 y 99999999.</param>
!!!<returns>True=Error o False=Todo bien </returns>
CargarDocumentoAsociado Procedure(String pNumeroLinea, String pCodigoComprobante, String pNumeroPos, String pNumeroComprobante),Byte


!!!<summary>Este comando permite almacenar los datos del beneficiario de una donaci�n en la memoria de trabajo de la</summary>
!!!<summary>impresora fiscal, y para su posterior impresi�n en el encabezado de un Comprobante Donaci�n pr�ximo a emitir.</summary>
!!!<param name="pRazonSocial" Raz�n Social del beneficiario.</param>
!!!<param name="pNumeroDocumento" N�mero del Documento del beneficiario.</param>
!!!<param name="pTipoDocumentoCliente" Tipo de Documento del cliente. (AH2G:TipoDocumentoCliente)</param>
!!!<param name="pDomicilio" Domicilio del beneficiario.</param>
!!!<returns>True=Error o False=Todo bien </returns>
CargarBeneficiario Procedure(String pRazonSocial, String pNumeroDocumento, String pTipoDocumentoCliente, String pDomicilio),Byte


!!!<summary>Este comando permite almacenar los datos del transportista en la memoria de trabajo de la impresora fiscal, y</summary>
!!!<summary>para su posterior impresi�n en el Remito ('R' � 'X') pr�ximo a emitir. El comando CargarTransportista</summary>
!!!<summary>debe enviarse antes del comando de apertura del Remito ('R' � 'X'), ya que es este �ltimo comando quien realiza la</summary>
!!!<summary>impresi�n.</summary>
!!!<param name="pRazonSocial"> Raz�n Social del transportista.</param>
!!!<param name="pCUIT"> CUIT del transportista.</param>
!!!<param name="pDomicilio"> Domicilio del transportista.</param> 
!!!<param name="pNombreChofer"> Nombre del chofer.</param>
!!!<param name="pTiposDeDocumentoCliente"> Enumeraci�n (TiposDeDocumentoCliente)</param>
!!!<param name="pNumeroDocumento"> N�mero del Documento del chofer.</param>
!!!<param name="pDominio1"> Dominio 1 del chofer.</param>
!!!<param name="pDominio2"> Dominio 2 del chofer.</param>
!!!<returns>True=Error o False=Todo bien </returns>
CargarTransportista Procedure(String pRazonSocial, String pCUIT, String pDomicilio, String pNombreChofer, String pTiposDeDocumentoCliente, String pNumeroDocumento, String pDominio1, String pDominio2),Byte


!!!<summary>Este comando permite extender la descripci�n de un �tem, y debe enviarse en forma previa a la impresi�n del</summary>
!!!<summary>�tem cuya descripci�n extiende. El comando ImprimirTextoFiscal puede ser enviado hasta un m�ximo de</summary>
!!!<summary>4 veces consecutivas en forma previa a la impresi�n del �tem.</summary>
!!!<param name="pTexto"> Texto a Imprimir.</param>
!!!<param name="pAtributos"> Pude ser DobleAncho, Centrado, Negrita o la combinatoria de los tres atributos separado por una coma.</param>
!!!<param name="pModoDisplay"> Toma el valor DisplayNo o DisplaySi. Default: DisplayNo).</param>
!!!<returns>True=Error o False=Todo bien </returns>
ImprimirTextoFiscal         Procedure(String pTexto, <String pAtributos>, <String pModoDisplay>),Byte


!!!<summary>Este comando permite la impresi�n de un �tem en el comprobante. En caso de ser necesario extender la</summary>
!!!<summary>descripci�n del �tem, en forma previa a este comando se puede enviar (hasta un m�ximo de 4 veces consecutivas)</summary>
!!!<summary>el comando ImprimirTextoFiscal.</summary>
!!!<summary>Para mas detalle del comando ir al manual de comandos</summary>
!!!<param name="pDescripcion">Descripci�n.</param>
!!!<param name="pCantidad">Cantidad. M�xima cantidad de d�gitos enteros: 9. M�xima cantidad de d�gitos decimales: 9</param>
!!!<param name="pPrecioUnitario">Precio por unidad de medida. M�xima cantidad de d�gitos enteros: 9.M�xima cantidad de d�gitos decimales: 4</param>
!!!<param name="pCondicionIVA">Condici�n de IVA. Enumeraci�n (AH2G:CondicionIVA:)</param>
!!!<param name="pAlicuotaIVA">Al�cuota de IVA (nn.nn). M�xima cantidad de d�gitos enteros: 2. M�xima cantidad de d�gitos decimales: 2. Valor por omisi�n: 0.00</param>
!!!<param name="pOperacionMonto">Operaci�n de suma o resta. Enumeraci�n (AH2G:ModoDeMonto:)</param>
!!!<param name="pTipoImpuestoInterno">Tipo de Impuesto Interno. Enumeraci�n (AH2G:ModoDeImpuestosInternos:). Valor por omisi�n: IIVariableKIVA (0)</param>
!!!<param name="pMagnitudImpuestoInterno">Magnitud del Impuesto Interno -coeficiente/monto/porcentaje. M�xima cantidad de d�gitos enteros: 9. M�xima cantidad de d�gitos decimales: 8</param>
!!!<param name="pModoDisplay"> Toma el valor DisplayNo o DisplaySi. Default: DisplayNo).</param>
!!!<param name="pModoBaseTotal">Operaci�n por Base o por Total. ModoPrecioBase=Precio base especificado. ModoPrecioTota=Precio total especificado.</param>
!!!<param name="pUnidadReferencia">Unidad de referencia. Rango permitido: Entre 0 y 99999999</param>
!!!<param name="pCodigoProducto">C�digo Producto/Servicio. (De Barra)Se trata de una codificaci�n cuya estructura es la provista por la Asociaci�n Argentina de Codificaci�n de Productos Comerciales. Ver Manual</param>
!!!<param name="pCodigoInterno">C�digo interno del sistema.</param>
!!!<param name="pUnidadMedida">C�digo unidad de medida. Enumeraci�n (AH2G:UnidadMedida:) Valor por omisi�n: AH2G:UnidadMedida:Unidad</param>
!!!<returns>True=Error o False=Todo bien </returns>
ImprimirItem  Procedure(String pDescripcion, String pCantidad, String pPrecioUnitario, String pCondicionIVA, String pAlicuotaIVA, String pOperacionMonto, | 
                        String pTipoImpuestoInterno, String pMagnitudImpuestoInterno, String pModoDisplay, String pModoBaseTotal, String pUnidadReferencia, |
                        String pCodigoProducto, String pCodigoInterno, String pUnidadMedida),Byte



!!!<summary>Este comando permite la impresi�n de un descuento aplicado sobre el �ltimo �tem incluido en el comprobante.</summary>
!!!<summary>Si bien el comando ImprimirDescuentoItem es aceptado en un Recibo 'X', la generaci�n de dicho</summary>
!!!<summary>comprobante puede resolverse empleando �nicamente el comando Imprimiritem. En los casos de emisi�n de</summary>
!!!<summary>Remitos 'R' o 'X', y Documento Donaci�n, el comando ImprimirDescuentoItem no es aceptado.</summary>
!!!<param name="pDescripcion">Descripci�n.</param>
!!!<param name="pMonto">Monto del Descuento. M�xima cantidad de d�gitos enteros: 9. M�xima cantidad de d�gitos decimales: 2</param>
!!!<param name="pModoDisplay"> Toma el valor DisplayNo o DisplaySi. Default: DisplayNo).</param>
!!!<param name="pModoBaseTotal">Operaci�n por Base o por Total. ModoPrecioBase=Precio base especificado. ModoPrecioTota=Precio total especificado.</param>
!!!<returns>True=Error o False=Todo bien </returns>
ImprimirDescuentoItem   Procedure(String pDescripcio, String pMonto, String pModoDisplay, String pModoBaseTotal),Byte


CerrarDocumento             Procedure(String pCopias, <String pDireccionEMail>),Byte

Cancelar                    Procedure(),Byte

CierreX                     Procedure(),Byte

CierreZ                     Procedure(),Byte

!!!<summary>Este comando permite consultar los datos fiscales del emisor de los comprobantes.</summary>
!!!<param name="pInformacion">N�mero de dato a devolver: 1=CUIT, 2=RazonSocial, 3=Registro, 4=NumeroPos, 5=FechaInicioActividades, 6=IngBrutos, 7=ResponsabilidadIVA</param>
ConsultarDatosInicializacion Procedure(Byte pInformacion),String

!ConsultarAcumuladosComprobanteOLD Procedure(String pCodigoComprobante, String pNumeroComprobante, Byte pInformacion),String

ConsultarAcumuladosComprobante Procedure(String pCodigoComprobante, String pNumeroComprobante, AH2G:SGCAC pGCAC, Byte pMostrarError)

ImprimirOtrosTributos   Procedure(String pCodigo, String pDescripcion, String pBaseImponible, String pImporte),Byte

ImprimirPago    Procedure(String pDescripcion, String pMonto, String pOperacion, String pModoDisplay, String pDescripcionAdicional, String pCodigoFormaPago, String pCuotas, String pCupones, String pReferencia),Byte        

ConsultarFechaHora   Procedure(*String pFecha, *String pHora)

PedirReimpresion    Procedure(),Byte

CopiarComprobante Procedure(String pCodigoComprobante, String pNumeroComprobante),Byte

SendRequest                 Procedure(String pCommando),Byte




                        End