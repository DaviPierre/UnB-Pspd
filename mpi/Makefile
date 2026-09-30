# Variáveis padrão (podem ser sobrescritas no terminal)
FILE ?= pi_linear.c
X ?= 4

# Define os nomes dos executáveis baseados no nome do arquivo original
EXEC_SEQ = $(FILE:.c=_seq)
EXEC_MPI = $(FILE:.c=_mpi)

# ==========================================
# 1. C Padrão (Sequencial)
# ==========================================
run: $(EXEC_SEQ)
	./$(EXEC_SEQ)

$(EXEC_SEQ): $(FILE)
	gcc $(FILE) -o $(EXEC_SEQ) -Wall

# ==========================================
# 2. MPI (Paralelo)
# ==========================================
runMpi: $(EXEC_MPI)
	mpirun -np $(X) ./$(EXEC_MPI)

$(EXEC_MPI): $(FILE)
	mpicc $(FILE) -o $(EXEC_MPI) -Wall

# ==========================================
# 3. Limpeza
# ==========================================
clean:
	rm -f *_seq *_mpi
