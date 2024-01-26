datos <- read.csv("out/plot_var.txt",sep="")
head(datos)
plot(datos$X2,datos$X1100,type="l",col="blue",lwd=3,xlab="Número de componentes", ylab="Varianza explicada acomulada")